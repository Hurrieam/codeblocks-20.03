#!/bin/sh

#
# This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
# http://www.gnu.org/licenses/gpl-3.0.html
#
# $Revision: 8917 $
# $Id: updateChangeLog.sh 8917 2013-03-24 04:46:09Z biplab $
# $HeadURL: svn://svn.code.sf.net/p/codeblocks/code/branches/release-20.xx/updateChangeLog.sh $
#

REV_TO=${1:-"HEAD"}
REV_LAST=`cat ChangeLog | head -3 - | tr -d '\r\n' | sed -e 's/.*svn\([0-9]*\).*/\1/'`

REV_MAX=`svn --xml info 'http://svn.code.sf.net/p/codeblocks/code/trunk' | tr -d '\r\n' | sed -e 's/.*<commit.*revision="\([0-9]*\)".*<\/commit>.*/\1/'`

REV_FROM=${2:-$(($REV_LAST + 1))}

if [ $REV_FROM -gt $REV_MAX ]; then
	exit 0;
fi

echo "Downloading svn-log from revision $REV_FROM to revision $REV_MAX" 

svn --verbose --xml log 'http://svn.code.sf.net/p/codeblocks/code/trunk' -r "$REV_TO:$REV_FROM" | xsltproc --stringparam strip-prefix "trunk"  --stringparam linelen "75" --stringparam groupbyday "no" --stringparam separate-daylogs "no"  --stringparam include-rev "yes" --stringparam breakbeforemsg "no" --stringparam reparagraph "no" --stringparam authorsfile "" --stringparam title "ChangeLog" --stringparam revision-link "#r" --stringparam ignore-message-starting "" --nowrite --nomkdir --nonet "ChangeLog.xsl" - > "ChangeLog.new"

cat "ChangeLog" >> "ChangeLog.new"

mv "ChangeLog.new" "ChangeLog"

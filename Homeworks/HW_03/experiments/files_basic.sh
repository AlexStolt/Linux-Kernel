#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;0;32m'
NC='\033[0m'

CURRENT_DIR=$PWD

#Get Root Directory
echo -n "Enter Absolute Path of Root Directory: "
read rootdir

#Set Root Directory
if [[ -d $rootdir ]]
then
  printf "${GREEN}Root Directory Set: $rootdir${NC}\n"
else
  printf "${RED}[ERROR/NOT FOUND] Root Directory${NC}\n"
  exit 1
fi

#Get Root Directory
echo -n "Enter Absolute Path of Mount Directory: "
read mountdir

#Set Root Directory
if [[ -d $mountdir ]]
then
  printf "${GREEN}Mount Directory Set: $mountdir${NC}\n"
else
  printf "${RED}[ERROR/NOT FOUND] Mount Directory${NC}\n"
  exit 1
fi

STORAGE="$rootdir/.storage/"
META="$rootdir/.meta/"

#Clear Storage
if [[ -d $STORAGE ]]
then
  #Clear Storage
  printf "    ${GREEN}[*]${NC} Clearing $STORAGE\n"
  cd $STORAGE
  rm * -r
fi

#Clear Meta
if [[ -d $META ]]
then
  #Clear Meta
  printf "    ${GREEN}[*]${NC} Clearing $META\n"
  cd "$rootdir/.meta/"
  rm * -r
fi

#Clear Root Directory
printf "    ${GREEN}[*]${NC} Clearing $rootdir\n"
cd $rootdir
rm * -r


#Back to Working Directory
cd $CURRENT_DIR

#Create Two Files of Same Size and Content
printf "    ${GREEN}[*]${NC} Creating Two 8KiB Files with the Same Content (Perl Script)...\n"
FILE_ONE='FILE_ONE'
FILE_TWO='FILE_TWO'
perl -e 'print "A" x 8192' > $FILE_ONE
perl -e 'print "A" x 8192' > $FILE_TWO

#Create One File with Different Content
printf "    ${GREEN}[*]${NC} Creating One 4KiB File with the Different Content (Perl Script)...\n"
FILE_THREE='FILE_THREE'
perl -e 'print "B" x 4096' > $FILE_THREE


#Copy the Tree Files in The Mount Directory
printf "    ${GREEN}[*]${NC} Copying Files to Mount (BB_WRITE)...\n"
cp $FILE_ONE $mountdir
cp $FILE_TWO $mountdir
cp $FILE_THREE $mountdir

#Hold Paths of The Three Files
FILE_ONE_PATH="$CURRENT_DIR/$FILE_ONE"
FILE_TWO_PATH="$CURRENT_DIR/$FILE_TWO"
FILE_THREE_PATH="$CURRENT_DIR/$FILE_THREE"

#Compare Files
printf "    ${GREEN}[*]${NC} Differences Between $FILE_ONE at Working Directory and Mount (BB_READ)...\n"
diff $FILE_ONE_PATH "$mountdir/$FILE_ONE"

printf "    ${GREEN}[*]${NC} Differences Between $FILE_TWO at Working Directory and Mount (BB_READ)...\n"
diff $FILE_TWO_PATH "$mountdir/$FILE_TWO"

printf "    ${GREEN}[*]${NC} Differences Between $FILE_THREE at Working Directory and Mount (BB_READ)...\n"
diff $FILE_THREE_PATH "$mountdir/$FILE_THREE"

#Display Storage Content
printf "    ${GREEN}[*]${NC} Storage Content at: $STORAGE: ${GREEN}"
ls $STORAGE
printf "${NC}"

#Display Meta Content
printf "    ${GREEN}[*]${NC} Meta Content at: $META: ${GREEN}"
ls $META
printf "${NC}"
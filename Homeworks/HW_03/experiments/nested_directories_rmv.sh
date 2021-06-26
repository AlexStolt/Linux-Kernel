#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;0;32m'
NC='\033[0m'

CURRENT_DIR=$PWD

#Disable the Deletion of Hidden Files
shopt -u dotglob


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
  rm -f *
fi

#Clear Meta
if [[ -d $META ]]
then
  #Clear Meta
  printf "    ${GREEN}[*]${NC} Clearing $META\n"
  cd "$rootdir/.meta/"
  rm -f *
fi

#Clear Root Directory
printf "    ${GREEN}[*]${NC} Clearing $rootdir\n"
cd $rootdir
rm -rf *


#Back to Working Directory
cd $CURRENT_DIR

#Create Two Files of Same Size and Content
printf "    ${GREEN}[*]${NC} Creating Two Nested Directories...\n"
LAYER_ONE='LAYER_ONE'
LAYER_TWO='LAYER_TWO'
mkdir "$mountdir/$LAYER_ONE"
mkdir "$mountdir/$LAYER_ONE/$LAYER_TWO"


#Create Two Files of Same Size and Content
printf "    ${GREEN}[*]${NC} Creating Two 8KiB Files with the Same Content (Perl Script)...\n"
FILE_ONE='FILE_ONE'
FILE_TWO='FILE_TWO'
perl -e 'print "A" x 8192' > $FILE_ONE
perl -e 'print "A" x 8192' > $FILE_TWO

#Create One File with Different Content
printf "    ${GREEN}[*]${NC} Creating Two 4KiB Files with the Same Content (Perl Script)...\n"
FILE_THREE='FILE_THREE'
FILE_FOUR='FILE_FOUR'
perl -e 'print "B" x 4096' > $FILE_THREE
perl -e 'print "B" x 4096' > $FILE_FOUR

#Copy the Tree Files in The Mount Directory
printf "    ${GREEN}[*]${NC} Copying Files to Mount's Layer One and Two (BB_WRITE)...\n"
cp $FILE_ONE "$mountdir/$LAYER_ONE"
cp $FILE_TWO "$mountdir/$LAYER_ONE/$LAYER_TWO"
cp $FILE_THREE $mountdir
cp $FILE_FOUR "$mountdir/$LAYER_ONE"

#Hold Paths of The Three Files
FILE_ONE_PATH="$CURRENT_DIR/$FILE_ONE"
FILE_TWO_PATH="$CURRENT_DIR/$FILE_TWO"
FILE_THREE_PATH="$CURRENT_DIR/$FILE_THREE"
FILE_FOUR_PATH="$CURRENT_DIR/$FILE_FOUR"

#Compare Files
printf "    ${GREEN}[*]${NC} Differences Between $FILE_ONE at Working Directory and Mount (BB_READ)...\n"
diff $FILE_ONE_PATH "$mountdir/$LAYER_ONE/$FILE_ONE"

printf "    ${GREEN}[*]${NC} Differences Between $FILE_TWO at Working Directory and Mount (BB_READ)...\n"
diff $FILE_TWO_PATH "$mountdir/$LAYER_ONE/$LAYER_TWO/$FILE_TWO"

printf "    ${GREEN}[*]${NC} Differences Between $FILE_THREE at Working Directory and Mount (BB_READ)...\n"
diff $FILE_THREE_PATH "$mountdir/$FILE_THREE"

printf "    ${GREEN}[*]${NC} Differences Between $FILE_FOUR at Working Directory and Mount (BB_READ)...\n"
diff $FILE_THREE_PATH "$mountdir/$LAYER_ONE/$FILE_FOUR"

#Display Storage Content
printf "    ${GREEN}[*]${NC} Storage Before Removing All Content: $STORAGE: ${GREEN}"
ls $STORAGE
printf "${NC}"

#Display Meta Content
printf "    ${GREEN}[*]${NC} Meta Before Removing All Content: $META: ${GREEN}"
ls $META
printf "${NC}"


#Remove Content
printf "    ${GREEN}[*]${NC} Content Deletion (BB_UNLINK)${GREEN}\n"
cd $mountdir
rm * -r

#Display Storage Content
printf "    ${GREEN}[*]${NC} Storage After Removing All Content: $STORAGE${GREEN}\n"
ls $STORAGE
printf "${NC}"

#Display Meta Content
printf "    ${GREEN}[*]${NC} Meta After Removing All Content: $META${GREEN}\n"
ls $META
printf "${NC}"

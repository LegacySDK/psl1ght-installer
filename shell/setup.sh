#!/bin/bash

# made by miskkaaa & hlelo120 :3

CYAN='\033[0;36m'
REDB='\033[1;31m'
GREN='\033[1;32m'
CLER='\033[0m'     # sorry i have to make this pretty, dont ask why its CLER not like CL or CLEAR

INSTALL_PATH="/opt/ps3dev"

rainbow() { # i stole this >:3
    local text="$*"
    local len=${#text}
    local i r g b

    for ((i=0; i<len; i++)); do
        local h=$(( i * 360 / (len > 1 ? len - 1 : 1) ))
        local x=$(( (60 - (h % 120 - 60 < 0 ? -(h % 120 - 60) : (h % 120 - 60))) * 255 / 60 ))

        case $((h / 60)) in
            0) r=255; g=$x;   b=0   ;;
            1) r=$x;  g=255;  b=0   ;;
            2) r=0;   g=255;  b=$x  ;;
            3) r=0;   g=$x;   b=255 ;;
            4) r=$x;  g=0;    b=255 ;;
            *) r=255; g=0;    b=$x  ;;
        esac

        echo -ne "\e[38;2;${r};${g};${b}m${text:i:1}"
    done

    echo -e "\e[0m"
}

rainbow "--------------------------------------------------"
echo -e "            Made by ${CYAN}Hlelo${CLER} and ${CYAN}miskaa${CLER}!"
echo -e " Join our discord! ${GREN}https://discord.gg/s7ynJawdPq${CLER}"
rainbow "--------------------------------------------------"

URLPRIMARY="https://hlelo.cc/files/ps3dev.zip"
URLSECONDARY="https://miskaa.pl/upload/ps3dev.zip"

if [ -n "$1" ]; then
    INSTALL_PATH="$1"
fi

if [ "$EUID" -ne 0 ] && [ -z "$1" ]; then
    echo -e "This script ${REDB}needs${CLER} to be ran via sudo or root, so it can install to ${CYAN}$INSTALL_PATH${CLER}!"
    echo -e "Or... You can use arguments like ${CYAN}$0 ~/InsertPathHere ${CLER}"
    exit 1
fi

mkdir -p "${INSTALL_PATH}/tmp"
tmp="${INSTALL_PATH}/tmp"

echo "plz gimme a sec (this part can take a bit)"

STATUS=$(curl --connect-timeout 2 --max-time 3 -s -o /dev/null -L -w "%{http_code}" "$URLPRIMARY")

if [ "$STATUS" = "200" ] || [ "$STATUS" = "301" ] || [ "$STATUS" = "302" ]; then
    echo -e "${URLPRIMARY} is ${GREN}HEALTHY${CLER}"
    DOWNLOAD_URL="$URLPRIMARY"
else
    STATUS_SECONDARY=$(curl -s -o /dev/null -L -w "%{http_code}" "$URLSECONDARY")
    echo -e "${URLPRIMARY} is sadly ${REDB}unavailable${CLER} 3:, trying miskaa.pl"

    if [ "$STATUS_SECONDARY" -eq 200 ] || [ "$STATUS_SECONDARY" -eq 301 ] || [ "$STATUS_SECONDARY" -eq 302 ]; then
        echo -e "usin ${URLSECONDARY} since its status code is ${STATUS_SECONDARY}"
        DOWNLOAD_URL="$URLSECONDARY"
    else
        echo -e "${URLSECONDARY} is also ${REDB}unavailable${CLER}.. quitting"
        # echo -e "${REDB}Both hlelo's and mine ${CLER}(miska's)${REDB} servers are unavailable, quitting${CLER}"
        exit 1
    fi
    # DOWNLOAD_URL="$URLSECONDARY"
fi

ZIP_FILE="$tmp/ps3dev.zip"

if [ -f "$ZIP_FILE" ]; then
    echo "skipping"
else
    echo "Downloading ${DOWNLOAD_URL}"
    curl -L "$DOWNLOAD_URL" -o "$ZIP_FILE"

    if [ $? -ne 0 ]; then
        echo "Download failed 3:"
        exit 1
    fi
fi

if ! command -v unzip &> /dev/null; then
    echo -e "${REDB}'unzip' is not installed! Quitting...${CLER}"
    exit 1
fi

if ! command -v make &> /dev/null; then
    echo -e "${REDB}'make' is not installed! Quitting...${CLER}"
    exit 1
fi

unzip -q -o "$ZIP_FILE" -d "$INSTALL_PATH"

if [ $? -eq 0 ]; then
    if [ -d "${INSTALL_PATH}/ps3dev" ]; then
        mv "${INSTALL_PATH}/ps3dev/"* "${INSTALL_PATH}/" 2>/dev/null

        if [ -d "${INSTALL_PATH}/psl1ght" ]; then
            # They'll never know...
            rm -rf "${INSTALL_PATH}/psl1ght"
        fi

        rm -rf "${INSTALL_PATH}/ps3dev"
        rm -rf "$tmp"
    fi
else
    echo -e "${REDB}Extraction failed!${CLER}"
    exit 1
fi

echo -e "Extracted!"
echo -e "please give me a moment"

mkdir "${INSTALL_PATH}/INSTALL_PSL1GHT"

USERNAME="${SUDO_USER:-$USER}"
echo -e "${CYAN}Setting ownership of ${INSTALL_PATH} to ${USERNAME}...${CLER}"
chown -R "${USERNAME}:" "$INSTALL_PATH"

# all of these are local btw
export PS3DEV="${INSTALL_PATH}" # dont ask
export PSL1GHT="${INSTALL_PATH}/INSTALL_PSL1GHT"
export PATH="$PS3DEV/ppu/bin:$PS3DEV/spu/bin:$PATH"

USER_HOME=$(eval echo ~${SUDO_USER:-$USER})

echo -e "\n${CYAN}Adding environment variables to .bashrc...${CLER}"

cat << EOF >> "$USER_HOME/.bashrc"
export PS3DEV="$INSTALL_PATH"
export PSL1GHT="$INSTALL_PATH/INSTALL_PSL1GHT"
export PATH="\$PS3DEV/ppu/bin:\$PS3DEV/spu/bin:\$PATH"
EOF

cd "${PS3DEV}/PSL1GHT"
make install-ctrl
make
make install

rainbow "--------------------------------------------------"
echo -e "${CYAN}Trying to compile something, please wait...${CLER}"
rainbow "--------------------------------------------------"
cd "${PS3DEV}/PSL1GHT/samples/sys/msgdialog"
make clean
make

rainbow "--------------------------------------------------"
echo -e "If it did not error or anything, congratulations!"
rainbow "--------------------------------------------------"

echo -e "${GREN}Done! Please restart your terminal or run 'source ~/.bashrc'${CLER}"

#!/bin/bash

q() {
    tput cnorm
    echo "Quitting.."
    exit 0
}

clear
echo "Kalandra v0.0.0 Self-Installer"
echo
read -p "Do you agree to the license? (Y/N): " answer
case "$answer" in
    [Yy])
        ;;
    [Nn])
        clear
        echo "FATAL: License agreement is required."
        q
        ;;
    *)
        clear
        echo "FATAL: Invalid input"
        q
        ;;
esac
clear

if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    OS=$(uname -s)
fi

if ! which gcc > /dev/null 2>&1; then
    clear
    echo "Kalandra v0.0.0 Self-Installer
    "
    echo "GCC is not installed."
    read -p "Do you wish to install it? (Y/N): " answer

    case "$answer" in
        Yy)
            echo "Installing: gcc.."
            case "$OS" in
                ubuntu|debian)
                    sudo apt-get update
                    sudo apt-get install -y gcc
                    ;;
                fedora)
                    sudo dnf install -y gcc
                    ;;
                arch)
                    sudo pacman -Syu --noconfirm gcc
                    ;;
                *)
                    clear
                    echo "FATAL: Unsupported package manager"
                    q
                    ;;
            esac
            ;;
        Nn)
            clear
            echo "FATAL: Missing depend: gcc"
            q
            ;;
        *)
            clear
            echo "FATAL: Invalid input"
            q
            ;;
    esac
    clear
fi

if ! which nasm > /dev/null 2>&1; then
    clear
    echo "Kalandra v0.0.0 Self-Installer
    "
    echo "NASM is not installed."
    read -p "Do you wish to install it? (Y/N): " answer

    case "$answer" in
        Yy)
            echo "Installing: nasm.."
            case "$OS" in
                ubuntu|debian)
                    sudo apt-get update
                    sudo apt-get install -y nasm
                    ;;
                fedora)
                    sudo dnf install -y nasm
                    ;;
                arch)
                    sudo pacman -Syu --noconfirm nasm
                    ;;
                *)
                    clear
                    echo "FATAL: Unsupported OS"
                    q
                    ;;
            esac
            ;;
        Nn)
            clear
            echo "FATAL: Missing depend: nasm"
            q
            ;;
        *)
            clear
            echo "FATAL: Invalid input"
            q
            ;;
    esac
    clear
fi

s=0
o=("x86 (8088)")
y=("+")
tput civis

d() {
    clear
    echo "Kalandra v0.0.0 Self-Installer

Select compiler output options:"

    for i in "${!o[@]}"; do
        if [ "$i" -eq "$s" ]; then
            echo -e "> [${y[i]}] ${o[i]}"
        else
            echo -e "  [${y[i]}] ${o[i]}"
        fi
    done

    echo "

SPACE   =   'Select/deselect'
ENTER   =   'Next section'
UP      =   'Cursor up'
DOWN    =   'Cursor down'
ENTER   =   'Next section'
Q       =   'Quit'"
}

# compiler output option select
while true; do
    d
    IFS= read -rsn1 i
    case "$i" in
        $'\x1b')
            IFS= read -rsn2 seq
            if [ "$seq" == "[A" ]; then
                if [ $s -gt 0 ]; then
                    s=$((s - 1))
                fi
            elif [ "$seq" == "[B" ]; then
                if [ $s -lt $((${#o[@]} - 1)) ]; then
                    s=$((s + 1))
                fi
            fi
            ;;
        ' ')
            if [ "${y[s]}" == "x" ]; then
                y[s]="+" 
            else
                y[s]="x"
            fi
            ;;
        "")
            break
            ;;
        q)
            clear
            q
            ;;
    esac
done

clear

# check for no selection
ax=true
for i in "${y[@]}"; do
    if [ "$i" != "x" ]; then
        ax=false
        break
    fi
done
if $ax; then
    echo "Fatal: No compiler output types selected."
    q
fi

# install path
clear
echo "Kalandra v0.0.0 Self-Installer

Enter install path (blank for /usr/bin):"
read -p "Install to: " answer

if [[ -z "$answer" ]]; then
    path="/usr/bin"
else
    path="$answer"
fi

clear
echo "Kalandra v0.0.0 Self-Installer

Installing to: $path"
read -p "Confirm? (Y/N): " answer
case "$answer" in
    [Yy])
        ;;
    [Nn])
        clear
        echo "Installation cancelled"
        q
        ;;
    *)
        clear
        echo "FATAL: Invalid input"
        q
        ;;
esac

# installing
clear
echo "Kalandra v0.0.0 Self-Installer
"

if [ "${y[0]}" != "x" ]; then
    echo "Installing KalandraCompiler (x86).."
    sudo gcc src/cli/klc.c src/core/compiler.c -o "$path/klc"
    if [ ! $? -eq 0 ]; then
        clear -x
        echo "FATAL: Build failed (scroll up)"
        q
    fi
fi
clear
echo "Done!"
q
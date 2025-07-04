#!/bin/bash
clear

q() {
    tput cnorm
    echo "Quitting.."
    exit 0
}


if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    OS=$(uname -s)
fi

if ! which gcc > /dev/null 2>&1; then
    echo "GCC is not installed."
    read -p "Do you wish to install it? (Y/N): " answer
    answer=$(echo "$answer" | tr '[:lower:]' '[:upper:]')

    if [[ "$answer" == "Y" ]]; then
        echo "Installing: gcc.."
        if [[ "$OS" == "ubuntu" || "$OS" == "debian" ]]; then
            sudo apt-get update
            sudo apt-get install -y gcc
        elif [[ "$OS" == "fedora" ]]; then
            sudo dnf install -y gcc
        elif [[ "$OS" == "arch" ]]; then
            sudo pacman -Syu --noconfirm gcc
        else
            clear
            echo "FATAL: Unsupported package manager"
            q
        fi
    elif [[ "$answer" == "N" ]]; then
        clear
        echo "FATAL: Missing depend: gcc"
        q
    else
        clear
        echo "FATAL: Invalid input"
        q
    fi
fi

if ! which nasm > /dev/null 2>&1; then
    echo "NASM is not installed."
    read -p "Do you wish to install it? (Y/N): " answer
    answer=$(echo "$answer" | tr '[:lower:]' '[:upper:]')

    if [[ "$answer" == "Y" ]]; then
        echo "Installing: nasm.."
        if [[ "$OS" == "ubuntu" || "$OS" == "debian" ]]; then
            sudo apt-get update
            sudo apt-get install -y nasm
        elif [[ "$OS" == "fedora" ]]; then
            sudo dnf install -y nasm
        elif [[ "$OS" == "arch" ]]; then
            sudo pacman -Syu --noconfirm nasm
        else
            clear
            echo "FATAL: Unsupported OS"
            q
        fi
    elif [[ "$answer" == "N" ]]; then
        clear
        echo "FATAL: Missing depend: nasm"
        q
    else
        clear
        echo "FATAL: Invalid input"
        q
    fi
fi


s=0
o=("x86 (8088)")
y=("+")
tput civis

d() {
    clear
    echo "Installer"
    echo ""
    echo "Select compiler output options:"

    for i in "${!o[@]}"; do
        if [ "$i" -eq "$s" ]; then
            echo -e "> [${y[i]}] ${o[i]}"
        else
            echo -e "  [${y[i]}] ${o[i]}"
        fi
    done

    echo "
    
ENTER   =   'Select/deselect'
UP      =   'Cursor up'
DOWN    =   'Cursor down'
SPACE   =   'Next section'
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
        "")
            if [ "${y[s]}" == "x" ]; then
                y[s]="+" 
            else
                y[s]="x"
            fi
            ;;
        ' ')
            break
            ;;
        q)
            clear
            q
            ;;
    esac
done

# check for no selection
ax=true
for i in "${y[@]}"; do
    if [ "$i" != "x" ]; then
        ax=false
        break
    fi
done
if $ax; then
    clear
    echo "Fatal: No compiler output types selected."
    q
fi

# installing
clear
echo "Compiling KalandraCompiler (x86)"
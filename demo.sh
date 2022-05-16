clear
echo "             _    _   _____    _____    _____   _        ______              _   _ ";
echo "     /\     | |  | | |  __ \  |_   _|  / ____| | |      |  ____|     /\     | \ | |";
echo "    /  \    | |  | | | |  | |   | |   | |      | |      | |__       /  \    |  \| |";
echo "   / /\ \   | |  | | | |  | |   | |   | |      | |      |  __|     / /\ \   | . \` |";
echo "  / ____ \  | |__| | | |__| |  _| |_  | |____  | |____  | |____   / ____ \  | |\  |";
echo " /_/    \_\  \____/  |_____/  |_____|  \_____| |______| |______| /_/    \_\ |_| \_|";
echo ""
echo "                     |  __ \  |  ____| |  \/  |  / __ \                            ";
echo "                     | |  | | | |__    | \  / | | |  | |                           ";
echo "                     | |  | | |  __|   | |\/| | | |  | |                           ";
echo "                     | |__| | | |____  | |  | | | |__| |                           ";
echo "                     |_____/  |______| |_|  |_|  \____/                            ";
echo "                                                                                   ";
echo "                                                                                   ";
echo "First, let's check the CLI help:"
echo ""
echo "AudiClean -h"
echo ""
read -p "---Press any key to continue---"
echo ""
src/AudiClean -h
echo ""
read -p "---Press any key to continue---"
clear
echo ""
echo "Next, lets check how to plot a filtered signal with the LMS filter:"
echo ""
echo "AudiClean -x wav-files/2harmonic441Hz.wav wav-files/sinewave882.wav output.wav"
echo ""
read -p "---Press any key to continue---"
nohup src/AudiClean -x wav-files/2harmonic441Hz.wav wav-files/sinewave882Hz.wav output.wav > /dev/null 2>&1&
echo $! > save_pid.txt
echo ""
read -p "---Press any key to continue---"
kill -9 `cat save_pid.txt`
wait `cat save_pid` 2>/dev/null
rm `save_pid.txt`
clear
echo "Now let's do it with the DNF:"
echo ""
echo "AudiClean -x -D wav-files/2harmonic441Hz.wav wav-files/sinewave882.wav output.wav"
echo ""
read -p "---Press any key to continue---"
nohup src/AudiClean -x -l 0.001 -D wav-files/2harmonic441Hz.wav wav-files/sinewave882Hz.wav output.wav > /dev/null 2>&1&
echo $! > save_pid.txt
echo ""
read -p "---Press any key to continue---"
kill -9 `cat save_pid.txt`
wait `cat save_pid` 2>/dev/null
rm `save_pid.txt`
clear
echo "Let's pipe the output from the filter to the standard audio device on this machine:"
echo ""
echo "AudiClean wav-files/2harmonic551Hz.wav wav-files/sinewave882Hz -d"
echo ""
read -p "---Press any key to continue---"
echo ""
src/AudiClean wav-files/2harmonic441Hz.wav wav-files/sinewave882Hz.wav -d
echo ""
read -p "---Press any key to continue---"
clear
echo "Let's pipe the output of AudiClean to a text-readable format!"
echo ""
echo "src/AudiClean wav-files/2harmonic441Hz.wav wav-files/sinewave882Hz.wav -t dat output.txt"
echo ""
read -p "---Press any key to continue---"
src/AudiClean wav-files/2harmonic441Hz.wav wav-files/sinewave882Hz.wav -t dat output.txt
echo ""
echo "View some samples: cat output.txt | head -n 100"
echo ""
read -p "---Press any key to continue---"
cat output.txt | head -n 100
echo ""
read -p "---Press any key to continue---"
clear
echo "Finally, lets use audio channels on this device to filter the noise reference in real-time and pipe it to the system output!"
echo ""
echo "Note: Sample rates and channel dimensions must be set, alsa is used to find the hardware sound devices"
echo "src/AudiClean -c 1 -r 44100 -t alsa hw:0 -c 1 -r 44100 -t alsa hw:2 -d"
echo ""
read -p "---Press any key to continue---"
src/AudiClean -q -V1 -c 1 -r 44100 -t alsa hw:0 -c 1 -r 44100 -t alsa hw:2 -d
echo ""
read -p "---Press any key to exit---"


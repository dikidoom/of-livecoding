echo "Press any key to stop watching."

update_app=0

while [ true ]
do
    # compile when .cpp changes
    for x in $(find . -name "*.cpp" -newer watchdog.sh)
    do
        echo ============================================================ compiling $x
        # ./compilelib.sh
        cppname=$(basename $x)
        soname=$(basename $x .cpp).so
        now=$(date +"%H:%M:%S")
        g++ -fPIC -shared $cppname -o $soname
        if [ $? -eq 0 ]
        then
            tput setaf 2
            # echo -e '\033[32m============================================================ WIN\033[0m'
            echo ------------------------------------------------------------ $now all fine
            tput setaf 9
        else
            tput setaf 1
            # echo -e '\033[31m============================================================ FAIL\033[0m'
            echo XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX $now ERROR
            tput setaf 9
        fi
        update_app=1
    done
    # on compilation,
    # update timestamp & send signal to app
    if [ $update_app -eq 1 ]
    then
        update_app=0
        # update this file's time stamp
        touch watchdog.sh
        # send signal 2 (SIGINT) to notify our app of the new lib
        pkill -2 dynamic
    fi
    # exit on keypress
    read -n1 -t2 space_pressed
    if [ $? -eq 0 ]
    then
        exit 0
    fi
done
      

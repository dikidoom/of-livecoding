echo "Press any key to stop watching."

update_app=0

while [ true ]
do
    # compile when .cpp changes
    for x in $(find . -name "*.cpp" -newer watchdog.sh)
    do
        echo compiling $x
        cppname=$(basename $x)
        soname=$(basename $x .cpp).so
        now=$(date +"%H:%M:%S")
        source trickycompile.sh $cppname $soname
        if [ $? -eq 0 ]
        then
            tput setaf 2
            echo done ------------------------------------------------------- $now
            tput setaf 9
            update_app=1
        else
            tput setaf 1
            echo fail XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX $now
            tput setaf 9
        fi
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
      

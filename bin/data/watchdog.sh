echo "Press any key to stop watching."

update_app=0

while [ true ]
do
    # compile when .cpp changes
    for x in $(find . -name "*.cpp" -newer watchdog.sh)
    do
        echo ============================================================ compiling $x
        ./compilelib.sh
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
      

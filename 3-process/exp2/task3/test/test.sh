#
# In a terminal
#
make clean
make

./test

#
# In annother terminal
#
ps -e | grep test
#   2556 pts/1    00:00:00 test
# For instance here: 2556

cat /proc/2556/ctx # Please instead of your own test's PID

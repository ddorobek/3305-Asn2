#test1
echo 128 > system.in
./myOS simulator ./tests/test1.txt
sleep 2
if grep -q "Unable to run job #1. Memory requirements exceed system capabilities" "system.out" ; then echo "Test 1 Succeeded" >> report.txt; else echo "Test 1 Failed" >> report.txt; fi
rm system.in

#test2
echo 128 > system.in
./myOS simulator ./tests/test2.txt
sleep 2
if grep -q "Starting job #1" "system.out" && grep -q "Job #1 completed" "system.out" ; then echo "Test 2 Succeeded" >> report.txt; else echo "Test 2 Failed" >> report.txt; fi
rm system.in

cat report.txt
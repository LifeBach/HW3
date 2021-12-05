time ../bin/hw3 ../testcases/n100.hardblocks ../testcases/n100.nets ../testcases/n100.pl ../output/n100.floorplan 0.1
time ../bin/hw3 ../testcases/n200.hardblocks ../testcases/n200.nets ../testcases/n200.pl ../output/n200.floorplan 0.1
time ../bin/hw3 ../testcases/n300.hardblocks ../testcases/n300.nets ../testcases/n300.pl ../output/n300.floorplan 0.1
echo "0.15"
time ../bin/hw3 ../testcases/n100.hardblocks ../testcases/n100.nets ../testcases/n100.pl ../output/n100.floorplan 0.15
time ../bin/hw3 ../testcases/n200.hardblocks ../testcases/n200.nets ../testcases/n200.pl ../output/n200.floorplan 0.15
time ../bin/hw3 ../testcases/n300.hardblocks ../testcases/n300.nets ../testcases/n300.pl ../output/n300.floorplan 0.15
# # cd ../verifier/
# # bash script_v.sh

cd ../..
tar -zcvf CS6135_HW3_109062468.tar.gz HW3
cp CS6135_HW3_109062468.tar.gz HW3_grading/student/109062468/CS6135_HW3_109062468.tar.gz
cd HW3_grading
bash HW3_grading.sh
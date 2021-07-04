clang -O3 -c ../../../../../container/median_queue.c ../../../../../container/qs_queue.c -I ../../../../../container/
clang -O3 -c ../../../code/random_numbers.c -I ../../../code/
clang++ -O3 -c ../../../code/compare_mq_qsq.cpp -I ../../../code/ -I ../../../../../container/
ld compare_mq_qsq.o median_queue.o qs_queue.o random_numbers.o -lc++ -lc

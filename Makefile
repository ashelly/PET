LIBS = -lrt
FLAGS = -O3 -s 
#FLAGS = -g 

all: ace tpt kev bhs pse snz phk ham null_eval

tables: tpt_tables.dat ham_table1.dat snz_tables.dat

null_eval:
	gcc -DTESTNUL=1 $(LIBS) $(FLAGS) speed_test.c  -onull_eval
null_sz:
	gcc -DTESTNUL=1 -s $(FLAGS) miniparse.c  -onull_sz


ace:
	gcc -DTESTACE=1 $(LIBS) $(FLAGS) speed_test.c ace_eval/source/ace_eval_best.c -oace
ace_sz:
	gcc -DTESTACE=1 -s $(FLAGS) miniparse.c ace_eval/source/ace_eval_best.c -oace_sz

tpt: tpt_tables.dat
	gcc -DTESTTPT=1 $(LIBS) $(FLAGS) speed_test.c twoplustwo/TPT_eval.c -otpt

tpt_tables.dat:
	gcc twoplustwo/generate_table.c --std=c99 perfecthash/source/fast_eval.c cactuskev/source/pokerlib.c -otwoplustwo/generate_table && twoplustwo/generate_table 

kev:
	gcc -DTESTKEV=1 $(LIBS) $(FLAGS) speed_test.c cactuskev/source/pokerlib.c -okev

phk:
	gcc -DTESTPHK=1 $(LIBS) $(FLAGS) speed_test.c perfecthash/PHK_eval.c perfecthash/source/fast_eval.c cactuskev/source/pokerlib.c -ophk

hes:
	gcc -DTESTHES=1  $(LIBS) $(FLAGS) speed_test.c showdown/HandEval.c -ohes

bhs:
	gcc -DTESTBHS=1  $(LIBS) $(FLAGS) speed_test.c showdown/source/HandEval.c -obhs
bhs_sz:
	gcc -DTESTBHS=1 -s $(FLAGS) miniparse.c showdown/source/HandEval.c -obhs_sz

pse:
	gcc -DTESTPSE=1  $(LIBS) $(FLAGS) speed_test.c -static -Lpokersource/source/lib/.libs -Ipokersource/source/include -lpoker-eval -opse

snz: snz_tables.dat
	gcc -DTESTSNZ=1  $(LIBS) $(FLAGS) speed_test.c senzee/SNZ_eval.c -osnz

snz_tables.dat:
	gcc -DTESTSNZ=1  $(LIBS) $(FLAGS) senzee/build_table.c cactuskev/source/pokerlib.c -osenzee/build_table  

ham: ham_table1.dat
	gcc -DTESTHAM=1  $(LIBS) $(FLAGS) speed_test.c hammer/source/handeval/handevaluator.c -oham

ham_table1.dat:
	cp hammer/source/handeval/eqcllist ./ham_table1.dat && cp hammer/source/handeval/carddag ./ham_table2.dat


specialk/libspecialk.a:
	g++ -c specialk/SPK_eval.cpp -o  specialk/SPK_eval.o
	g++ -c specialk/source/SevenEval.cpp  -o specialk/SevenEval.o 
	g++ -c specialk/source/FiveEval.cpp  -o specialk/FiveEval.o 
	ar crf specialk/libspecialk.a specialk/SevenEval.o specialk/FiveEval.o  specialk/SPK_eval.o


spk: specialk/libspecialk.a
	g++ -DTESTSPK=1 -lstdc++  $(LIBS) $(FLAGS) -x c speed_test.c  -Lspecialk -lspecialk  -Ispecialk/source -ospk


clean:
	rm ???

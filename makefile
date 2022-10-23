main: main.o view/view.o controller/controller.o model/model.o
	gcc -o main $^ -lMLV -ansi

main.o: main.c
	gcc -c $^ -ansi

view.o: view/view.c
	gcc -c $^ -ansi

model.o: model/model.c
	gcc -c $^ -ansi

controller.o: controller/controller.c
	gcc -c $^ -ansi

clean:
	rm *.o
	rm view/*.o
	rm controller/*.o
	rm model/*.o
	rm main
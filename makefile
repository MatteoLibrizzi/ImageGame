

game: main.o view.o controller.o model.o
	gcc -o game $^ -lMLV -ansi

main.o: main.c
	gcc -c $^ -ansi

view.o: view/view.c
	gcc -c $^ -ansi

model.o: model/model.c
	gcc -c $^ -ansi
	#gcc -c $^ -DREVERSE -ansi

controller.o: controller/controller.c
	gcc -c $^ -ansi

clean:
	rm *.o
	rm view/*.o
	rm controller/*.o
	rm model/*.o
	rm game
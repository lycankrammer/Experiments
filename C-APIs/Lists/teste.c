#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
	List_T list1;
	
	list1 = List_push(nullptr, "List");
	list1 = List_push(list1, "Arena");
	list1 = List_push(list1, "Mem");
	list1 = List_push(list1, "Atom");
	
	for (List_T p = list1; p; p = p->rest)
		printf("%s ", (char *) p->first);
	printf("\n");
	
	List_T list2 = List_list("Arara", "Anaconda", "Rich", nullptr);
	list1 = List_append(list1, list2);
	for (List_T p = list1; p; p = p->rest)
		printf("%s ", (char *) p->first);
	printf("\n");
		
	list1 = List_pop(list1, (void **){ 0 });
	for (List_T p = list1; p; p = p->rest)
		printf("%s ", (char *) p->first);
	printf("\n");
	
	list1 = List_push(list1, "Mathematics is Beautiful ");
	for (List_T p = list1; p; p = p->rest)
		printf("%s ", (char *) p->first);
	printf("\n");
			
	/* inteiros */	
	List_T list_nums;
	
	list_nums = List_push(nullptr, &(int){3});
	int *num;
	for (size_t i = 1; i <= 100; i++) {
		num = malloc(sizeof(*num));
		*num = i;
		list_nums = List_append(list_nums, List_push(nullptr, num));
	}
	for (List_T p = list_nums; p; p = p->rest)
		printf("%d ", *((int *) p->first));
	printf("\n");
	
	for (size_t i = 1; i <= 49; i++) {
		list_nums = List_pop(list_nums, (void **){ 0 });
	}
	for (List_T p = list_nums; p; p = p->rest)
		printf("%d ", *((int *) p->first));
	printf("\n");
	
	list_nums = List_reverse(list_nums);
	for (List_T p = list_nums; p; p = p->rest)
		printf("%d ", *((int *) p->first));
	printf("\n");
	
	/* reais */
	List_T list_reals = List_list(&(double){2.0E-12}, &(double){2.34}, &(double){9E10}, &(double){89012.9E1}, &(double){100000000.0}, &(double){12E-2}, nullptr);
	for (List_T p = list_reals; p; p = p->rest)
		printf("%g ", *((double *) p->first));
	printf("\n");
	
	
	return 0;
}

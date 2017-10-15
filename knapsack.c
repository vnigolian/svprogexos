#include <stdio.h>
#include <string.h> // for memcpy()
#include <stdlib.h> // for qsort()

#define SIZE 4

typedef struct		Object {
	double			weight;
	double			value;
}					Object;

/* ==========================================================================
 * This is the first algorithm:
 * solve it naively, in the given order.
 */
void				solve_naive(Object objects[], double remaining_weight) {
	double			value = 0.0;

	for (int i = 0; i < SIZE; i++) {
		printf("considering : w=%3.2f, v=%3.2f", objects[i].weight, objects[i].value);
		if (objects[i].weight <= remaining_weight) {
			value += objects[i].value;
			remaining_weight -= objects[i].weight;
			printf(" --> taking");
		}
		printf("\n");
	}
	printf("value = %3.2f, remaining weight = %3.2f\n\n", value, remaining_weight);
}

/* ==========================================================================
 * This is the second algorithm: greedy.
 */
int					comp(const void *elem1, const void *elem2) {
	Object			*a;
	Object			*b;

	a = (Object *)elem1;
	b = (Object *)elem2;
	if (a->value > b->value) {
		return (-1);
	} else if (a->value < b->value){
		return (1);
	}
	return (0);
}

void				solve_greedy(Object objects[], double remaining_weight) {
	Object			*sorted_objects;

	memcpy(&sorted_objects, &objects, sizeof((Object *)objects));
	qsort(sorted_objects, SIZE, sizeof(Object), comp);
	solve_naive(sorted_objects, remaining_weight);
}

/* ==========================================================================
 * This is the third algorithm: try all.
 */
Object				solve_exact_recursive(Object objects[], int start, double remaining_weight) {
	Object			result = { 0.0, 0.0 };
	double			value;
	double			weight;

	if (start < SIZE) {
		// 1) consider NOT taking first object
		result = solve_exact_recursive(objects, start + 1, remaining_weight);
		weight = result.weight;
		value = result.value;

		// 2) consider taking the first object, if possible
		if (objects[start].weight <= remaining_weight) {
			result = solve_exact_recursive(objects, start + 1, remaining_weight - objects[start].weight);
			result.value += objects[start].value;

			// 3) keep the best of the two
			if (value > result.value) {
				result.value = value;
				result.weight = weight;
			}
		}
	}

	return (result);
}

void				solve_exact(Object objects[], double remaining_weight) {
	Object			result;

	result = solve_exact_recursive(objects, 0, remaining_weight);
	printf("value = %3.2f, remaining weight = %3.2f\n\n", result.value, result.weight);
}

/* ========================================================================== */
int					main(void) {
	const double	max = 9.0;
	Object			objects[] = {
		{ 4.0,  8.0 },
		{ 2.0,  3.0 },
		{ 5.0,  7.0 },
		{ 6.0, 10.0 }
	};

	solve_naive(objects, max);
	solve_greedy(objects, max);
	solve_exact(objects, max);
	return (0);
}

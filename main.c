#include <stdio.h>
#include <malloc.h>

#define INPUT_FILE "in.txt"
#define OUTPUT_FILE "out.txt"

int* read_file(int *len) {
    FILE *f_in;
    int *mass;
    f_in = fopen(INPUT_FILE, "r");

    fscanf(f_in, "%d", len);
    mass = (int *) malloc(*len * sizeof(int));
    for (int i = 0; i < *len; i++)
        fscanf(f_in, "%d", mass + i);
    fclose(f_in);
    return mass;
}


void swap(int *mass, int first_ind, int second_ind) {
    int tmp;
    tmp = mass[second_ind];
    mass[second_ind] = mass[first_ind];
    mass[first_ind] = tmp;
}


void quick_sort(int* mass, int mass_first, int mass_end) {
    int pvt_ind = (mass_end + mass_first) / 2;
    int pvt_val = mass[pvt_ind];

    int cur_left = mass_first;
    int cur_right = mass_end;

    while (cur_right >= cur_left) {
        while (mass[cur_right] > pvt_val)
            cur_right--;
        while (mass[cur_left] < pvt_val)
            cur_left++;
        if (cur_right >= cur_left) {
            swap(mass, cur_left, cur_right);
            cur_left++;
            cur_right--;
        }
    }
    if (mass_first < cur_right)
        quick_sort(mass, mass_first, cur_right);
    if (cur_left < mass_end)
        quick_sort(mass, cur_left, mass_end);
}


int main() {
    int len;
    int *mass = read_file(&len);

    quick_sort(mass, 0, len - 1);
    FILE *f_out;
    f_out = fopen(OUTPUT_FILE, "a");
    for (int i = 0; i < len; i++)
        fprintf(f_out, "%d ", mass[i]);
    fclose(f_out);
    free(mass);
    return 0;
}

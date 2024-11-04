// main_dynamic.c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle = dlopen("./libcalc.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error: %s\n", dlerror());
        return 1;
    }

    int (*add)(int, int) = dlsym(handle, "add");
    int (*subtract)(int, int) = dlsym(handle, "subtract");
    int (*multiply)(int, int) = dlsym(handle, "multiply");
    double (*divide)(int, int) = dlsym(handle, "divide");

    int x = 10, y = 5;
    printf("Add: %d\n", add(x, y));
    printf("Subtract: %d\n", subtract(x, y));
    printf("Multiply: %d\n", multiply(x, y));
    printf("Divide: %.2f\n", divide(x, y));

    dlclose(handle);
    return 0;
}


# enum
```
#include <stdio.h>

enum TrafficLight {
    RED,
    YELLOW,
    GREEN
};

int main() {
    enum TrafficLight light = RED;

    if (light == RED) {
        printf("Stop!\n");
    } else if (light == GREEN) {
        printf("Go!\n");
    } else {
        printf("Wait!\n");
    }

    return 0;
}
```



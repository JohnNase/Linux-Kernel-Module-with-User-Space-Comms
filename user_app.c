#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/my_device"

int main() {
    int fd;
    char buffer[1024];

    // Open the device file
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return -1;
    }

    // Write to the device
    printf("Enter a string to write to the device: ");
    fgets(buffer, sizeof(buffer), stdin;
    if (write(fd, buffer, strlen(buffer)) < 0) {
        perror("Failed to write to the device");
        close(fd);
        return -1;
    }

    // Read from the device
    if (read(fd, buffer, sizeof(buffer)) < 0) {
        perror("Failed to read from the device");
        close(fd);
        return -1;
    }
    printf("Data read from the device: %s\n", buffer);

    // Close the device file
    close(fd);
    return 0;
}
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "my_device"
#define BUFFER_SIZE 1024

static int major_number;
static char buffer[BUFFER_SIZE];
static int buffer_offset;

// Function prototypes
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release,
};

// Called when the module is loaded
static int __init my_module_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "Registered device with major number %d\n", major_number);
    return 0;
}

// Called when the module is unloaded
static void __exit my_module_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Unregistered device\n");
}

// Called when a process opens the device file
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

// Called when a process closes the device file
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Called when a process reads from the device file
static ssize_t device_read(struct file *filep, char *user_buffer, size_t len, loff_t *offset) {
    int bytes_to_copy = min(len, (size_t)(BUFFER_SIZE - buffer_offset));
    if (bytes_to_copy == 0) {
        printk(KERN_INFO "No data to read\n");
        return 0;
    }
    if (copy_to_user(user_buffer, buffer + buffer_offset, bytes_to_copy)) {
        printk(KERN_ALERT "Failed to copy data to user\n");
        return -EFAULT;
    }
    buffer_offset += bytes_to_copy;
    printk(KERN_INFO "Read %d bytes from device\n", bytes_to_copy);
    return bytes_to_copy;
}

// Called when a process writes to the device file
static ssize_t device_write(struct file *filep, const char *user_buffer, size_t len, loff_t *offset) {
    int bytes_to_copy = min(len, (size_t)BUFFER_SIZE);
    if (copy_from_user(buffer, user_buffer, bytes_to_copy)) {
        printk(KERN_ALERT "Failed to copy data from user\n");
        return -EFAULT;
    }
    buffer_offset = 0;
    printk(KERN_INFO "Wrote %zu bytes to device\n", len);
    return len;
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple Linux kernel module");
MODULE_AUTHOR("Your Name");
extern int sprd_gpio_direction_output(struct gpio_chip *chip,
		                                        unsigned offset, int value);
extern int sprd_gpio_direction_input(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_get(struct gpio_chip *chip, unsigned offset);
extern void sprd_gpio_set(struct gpio_chip *chip, unsigned offset, int value);
extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);

#define I2C_GPIO_SYNC
#define I2C_ACTIVE do { } while (0)
#define I2C_TRISTATE do { } while (0)
#define I2C_DELAY udelay(5)	/* 1/4 I2C clock duration */

#define I2C_INIT \
       do { \
            sprd_gpio_request(NULL, CONFIG_SOFT_I2C_GPIO_NR_SCL); \
            sprd_gpio_request(NULL, CONFIG_SOFT_I2C_GPIO_NR_SDA); \
       } while (0)

#define I2C_READ sprd_gpio_get(NULL, CONFIG_SOFT_I2C_GPIO_NR_SDA)

#define I2C_SDA(bit) \
       do { \
             if (bit) \
	        sprd_gpio_direction_input(NULL, CONFIG_SOFT_I2C_GPIO_NR_SDA); \
	     else \
	        sprd_gpio_direction_output(NULL, CONFIG_SOFT_I2C_GPIO_NR_SDA, 0); \
	     I2C_GPIO_SYNC; \
       } while (0)

#define I2C_SCL(bit) \
       do { \
             sprd_gpio_direction_output(NULL, CONFIG_SOFT_I2C_GPIO_NR_SCL, bit); \
             I2C_GPIO_SYNC; \
       } while (0)

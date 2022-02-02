/*
* et200 spi driver for mtk
*/
#include "spi_et200.h"

#define    WAKE_TIME                        4
#define    WAIT_WAKEUP_TIME                  2000


//static struct gpio_desc *et200_rst_gpio;
//static struct gpio_desc *et200_rb_gpio;
static struct gpio_desc *et200_en_gpio;

static	int newgpio_rst;
static	int newgpio_rb;

static	int newgpio_wakeup;

void et200_spi_wakeup(int count)
{
	int i = 0;
	//mt_set_gpio_out(GPIO_SPI_WAKEUP_GPIO, GPIO_OUT_ZERO);
	
    gpio_set_value(newgpio_rst, 0);

	for(i = 0; i< count; i++)
	{
		udelay(40);
	}
    
	//mt_set_gpio_out(GPIO_SPI_WAKEUP_GPIO,  GPIO_OUT_ONE);


    gpio_set_value(newgpio_rst, 1);

	udelay(WAIT_WAKEUP_TIME);

	return;
}

int et200_spi_wake(int count)
{
	int try_count = 0;

	//while(0 != mt_get_gpio_in(GPIO_SPI_RB_GPIO))// check busy
        printk("et200_spi_wake gpio_rb start %d\n", gpio_get_value(newgpio_rb));	
	while(0 !=  gpio_get_value(newgpio_rb))
	{
		ET200_SPI_INFO("et200_spi_wake...............\n");

		if(try_count)
			mdelay(10);

		et200_spi_wakeup(count);

		mdelay(2);

		if(try_count)
			ET200_SPI_ERR("et200_spi_wake.......reset again ..,try_count = %d\n",try_count);

		if(try_count++ > 6)
		{   
			ET200_SPI_ERR("Wake failed\n");            
			return -1;
		}
	};
	printk("et200_spi_wake gpio_rb end %d\n", gpio_get_value(newgpio_rb));
	return 0;
}

static int et200_wait_ready(void)
{
	unsigned int time = 0;

	//ET200_SPI_TRACE;

	ET200_SPI_INFO("et200_wait_ready in........\n");

	//while(0 != mt_get_gpio_in(GPIO_SPI_RB_GPIO))// check busy
        printk("et200_wait_ready gpio_rb start %d\n", gpio_get_value(newgpio_rb));	
	while(0 !=  gpio_get_value(newgpio_rb))
	{
		time++;
		udelay(1);

		if(time>20000000)	//add delay for RSA 2048 Gen key
		{
			ET200_SPI_INFO("wait busy timeout!!\n");
			if(et200_spi_wake(WAKE_TIME))
				return -1; 
		}
	}
	if(time > 0)
	{
		ET200_SPI_INFO("wait busy %d us....\n", time);
	}
	printk("et200_wait_ready gpio_rb end %d\n", gpio_get_value(newgpio_rb));
	return 0;
}

static void et200_set_gpio(void)
{
	int ret =0;
	ET200_SPI_TRACE;

/*
	mt_set_gpio_mode(GPIO_SPI_RB_GPIO, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_SPI_RB_GPIO, GPIO_DIR_IN);
	mt_set_gpio_pull_enable(GPIO_SPI_RB_GPIO, GPIO_PULL_ENABLE);

	mt_set_gpio_mode(GPIO_SPI_WAKEUP_GPIO, GPIO_MODE_00);
	mt_set_gpio_dir(GPIO_SPI_WAKEUP_GPIO, GPIO_DIR_OUT);
	mt_set_gpio_pull_enable(GPIO_SPI_WAKEUP_GPIO, GPIO_PULL_ENABLE);
	mt_set_gpio_out(GPIO_SPI_WAKEUP_GPIO, GPIO_OUT_ONE);
*/


	/* Init sequence */
//    gpiod_set_value(et200_rst_gpio, 0);
//    mdelay(10);
//    gpiod_set_value(et200_rst_gpio, 1);
//	mdelay(10);
	
    gpio_request(newgpio_rb, "et200_gpio_rb");
    gpio_direction_input(newgpio_rb);


    gpio_request(newgpio_rst, "et200_gpio_rst");
    gpio_direction_output(newgpio_rst, 0);
    //udelay(20);
	mdelay(5);
    gpio_direction_output(newgpio_rst, 1);
	mdelay(500);


/*	
    gpio_request(newgpio_wakeup, "et200_gpio_wakeup");
    gpio_direction_output(newgpio_wakeup, 0);

	mdelay(1);
    gpio_direction_output(newgpio_wakeup, 1);

	mdelay(1);
	ret = gpio_get_value(newgpio_wakeup);
	printk("wz----     after set wakupe   newgpio_wakeup pin = %d \n", ret);
*/

	mdelay(1);
	ret = gpio_get_value(newgpio_rb);
	printk("et200 gpio_rb after  udelay 20 set wakupe   rb pin = %d \n", ret);

/*
    ret = gpio_get_value(newgpio_rb);
	printk("wz----     after  udelay 500 set wakupe   rb pin = %d \n", ret);
*/


	printk("et200: sequence init complete!\n");

	return;
}




static int et200_open(struct inode * inode, struct file *file)
{
	int ret = 0;
	ET200_SPI_TRACE;
	ret = nonseekable_open(inode, file);
	ET200_SPI_TRACE_OUT;
	return ret;
}


static long et200_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

	int ret = 0;
	struct veb_et200_data *et200_dev = NULL;
	struct miscdevice *miscdev = NULL;

	ET200_SPI_TRACE;

	miscdev = (struct miscdevice *)(file->private_data);
	et200_dev = (struct veb_et200_data *)dev_get_drvdata(miscdev->this_device);
	
	if (_IOC_TYPE(cmd) != ET200_IOCTL_MAGIC) 
	{
		ET200_SPI_ERR("et200_ioctl error cmd!\n");
		return -1;
	}
	cmd = _IOC_NR(cmd);

	switch (cmd) 
	{    
		case ET200_CHIP_CON_NEW:
		{
			/*var for spi*/
			struct spi_transfer xfer, xfer_left;
			struct spi_message p;
			unsigned char *tx_tmp = NULL;
			unsigned char *rx_tmp = NULL;
			/*var for control info*/
			et200_duplex_con et200_con;
			int count, left, length;
			unsigned char *tx_left, *rx_left;

			mutex_lock(&(et200_dev->dev_lock));
			ret = copy_from_user(&et200_con, (et200_duplex_con*)arg, sizeof(et200_duplex_con));
			count = et200_con.len;
			if(count < MAX_TRANSFER_LEN){
				left = count % 1024;
				length = count - left;
			}else if(count == MAX_TRANSFER_LEN){
				left = 0;
				length = MAX_TRANSFER_LEN;					
			}else /*(count > MAX_TRANSFER_LEN )*/{
				ET200_SPI_ERR("et200_ioctl data should not over 256K\n");
				mutex_unlock(&(et200_dev->dev_lock));
				goto func_error;
			}		

		#ifdef ET200_SPI_USE_MMAP
			if (ET200_ALREADY_MAPPED == et200_dev->mmapped){
			//use mmap for big data
				tx_tmp = (unsigned char*)et200_dev->mmap_addr;
				rx_tmp = (unsigned char *)et200_dev->mmap_addr + (ET200_MMAP_SIZE >> 1);
			}
		#endif

			#ifdef SPI_MSG_DUMP
			ET200_SPI_INFO("et200_ioctl: ET200_DUPLEX_CON_NEW mmap\n");
			ET200_SPI_INFO("et200_ioctl mmap dump count:%d left:%d\n", count, left);
			#endif

			ret = et200_wait_ready();  
			if(0 != ret)
			{
				mutex_unlock(&(et200_dev->dev_lock));
				goto func_error;
			}
			spi_message_init(&p);

			xfer.tx_buf     = tx_tmp;
			xfer.rx_buf     = rx_tmp;
			xfer.len        = length;
			xfer.speed_hz	= 1000000,
			xfer.cs_change  = 0;
			xfer.bits_per_word = BITS_PER_WORD;
			xfer.delay_usecs = 3;
			xfer.tx_nbits = SPI_NBITS_SINGLE;
			xfer.rx_nbits = SPI_NBITS_SINGLE;
			spi_message_add_tail(&xfer, &p);

			if(left){
				tx_left = tx_tmp + length;
				rx_left = rx_tmp + length;

				xfer_left.tx_buf     = tx_left;
				xfer_left.rx_buf     = rx_left;
				xfer_left.len        = left;
				xfer_left.speed_hz	= 1000000,
				xfer_left.cs_change  = 0;
				xfer_left.bits_per_word = BITS_PER_WORD;
				xfer_left.delay_usecs = 3;
				xfer_left.tx_nbits = SPI_NBITS_SINGLE;
				xfer_left.rx_nbits = SPI_NBITS_SINGLE;
				spi_message_add_tail(&xfer_left, &p);
			}

			#ifdef SPI_MSG_DUMP
			ET200_SPI_INFO("et200_ioctl: start sync\n");
			#endif

			ret = spi_sync(et200_dev->spi, &p);
			if(ret != 0)
			{
				ET200_SPI_ERR("spi sync failed(%d)!\n", ret);
			}
			
			#ifdef SPI_MSG_DUMP
			ET200_SPI_INFO("et200_ioctl: sync end\n");
			#endif

			#ifdef ET200_SPI_USE_MMAP
			if (ET200_ALREADY_MAPPED == et200_dev->mmapped){
				//nothing to do
			}
			#endif
			mutex_unlock(&(et200_dev->dev_lock));
			break;
		}
		default:
			ET200_SPI_ERR("et200_ioctl cmd error! cmd: %d \n", cmd);
			ret = -1;
			break;

	}
	ET200_SPI_TRACE_OUT;
	return ret;

func_error:
	ET200_SPI_ERR("et200_ioctl error\n");
	return -1;
}


static int et200_release(struct inode *inode, struct file *file)
{
	struct veb_et200_data *et200_dev = NULL;
	struct miscdevice *miscdev = NULL;
	ET200_SPI_TRACE;

	miscdev = (struct miscdevice *)(file->private_data);
	et200_dev = (struct veb_et200_data *)dev_get_drvdata(miscdev->this_device);
	mutex_lock(&(et200_dev->dev_lock));
	
	et200_dev->mmapped = ET200_NOT_MAPPED;
	
	mutex_unlock(&(et200_dev->dev_lock));
	ET200_SPI_TRACE_OUT;
	return 0;
}

static ssize_t et200_read(struct file *file, char __user *buf , size_t count, loff_t *f_pos)
{
	int ret = 0;
	unsigned char * rx_tmp = NULL;
	unsigned char * rx_left = NULL;

	int left, length;
	struct spi_transfer xfer, xfer_left;
	struct spi_message p;

	struct veb_et200_data *et200_dev = NULL;
	struct miscdevice *miscdev = NULL;
	ET200_SPI_TRACE;
	ret = gpio_get_value(newgpio_rb);
	printk("et200 gpio_rb  before read   rb pin = %d \n", ret);

	miscdev = (struct miscdevice *)(file->private_data);
	et200_dev = (struct veb_et200_data *)dev_get_drvdata(miscdev->this_device);
	mutex_lock(&(et200_dev->dev_lock));

	#ifdef SPI_MSG_DUMP
	ET200_SPI_INFO("et200_read dump count:%d \n", (unsigned int)count);
	#endif

	#ifdef ET200_SPI_USE_MMAP
	if (ET200_ALREADY_MAPPED == et200_dev->mmapped){
		rx_tmp = (unsigned char*)et200_dev->mmap_addr;
	}else
	#endif
	{
		rx_tmp = et200_dev->buffer;
	}

	if(count < MAX_TRANSFER_LEN){
		left = count % 1024;
		length = count - left;
	}else if(count == MAX_TRANSFER_LEN){
		left = 0;
		length = MAX_TRANSFER_LEN;
	}else /*(count > MAX_TRANSFER_LEN)*/{
		ET200_SPI_ERR("et200_read data should not over 256K\n");
		goto func_error;
	}

	#ifdef SPI_MSG_DUMP
	ET200_SPI_INFO("et200_read dump count:%d length:%d left:%d\n", (int)count, length, left);
	#endif

	ret = et200_wait_ready();  
	if(0 != ret)
	{
		goto func_error;
	}

	spi_message_init(&p);

	if(length > 0){
		xfer.tx_buf     = rx_tmp,
		xfer.rx_buf     = rx_tmp,
		xfer.len        = length,
		xfer.speed_hz	= 1000000,
		xfer.cs_change  = 0,
		xfer.bits_per_word = BITS_PER_WORD,
		xfer.delay_usecs = 3,
		xfer.tx_nbits = SPI_NBITS_SINGLE;
		xfer.rx_nbits = SPI_NBITS_SINGLE;
		spi_message_add_tail(&xfer, &p);
	}

	if(left){
		rx_left = rx_tmp + length;
		xfer_left.tx_buf     = rx_left,
		xfer_left.rx_buf     = rx_left,
		xfer_left.len        = left,
		xfer_left.speed_hz	= 1000000,
		xfer_left.cs_change  = 0,
		xfer_left.bits_per_word = BITS_PER_WORD,
		xfer_left.delay_usecs = 3,
		xfer_left.tx_nbits = SPI_NBITS_SINGLE;
		xfer_left.rx_nbits = SPI_NBITS_SINGLE;
		spi_message_add_tail(&xfer_left, &p);
	}

	#ifdef SPI_MSG_DUMP
	ET200_SPI_INFO("et200_read: start sync\n");
	#endif

	spi_sync(et200_dev->spi, &p);

	#ifdef SPI_MSG_DUMP
	ET200_SPI_INFO("et200_read: sync end\n");
	#endif

	#ifdef SPI_MSG_DUMP
	ET200_SPI_ARRAY_WITH_PREFIX("et200_read dump buffer :", rx_tmp, count);
	#endif

	#ifdef ET200_SPI_USE_MMAP
	if (ET200_ALREADY_MAPPED == et200_dev->mmapped){
		//nothing to do
	}else
	#endif
	{
		ret = copy_to_user(buf, rx_tmp, count);
	}
	mutex_unlock(&(et200_dev->dev_lock));
	ET200_SPI_TRACE_OUT;
	return count;

func_error:
	mutex_unlock(&(et200_dev->dev_lock));
	ET200_SPI_ERR("veb_et200_read error\n");
	return 0;
}

static ssize_t et200_write(struct file *file, const char __user *buf , size_t count, loff_t *f_pos)
{
	int ret = 0;
	unsigned char * tx_tmp = NULL;
	unsigned char * rx_tmp = NULL;
	unsigned char * tx_left = NULL;
	unsigned char * rx_left = NULL;

	int left, length;
	struct spi_transfer xfer, xfer_left;
	struct spi_message p;

	struct veb_et200_data *et200_dev = NULL;
	struct miscdevice *miscdev = NULL;

	ET200_SPI_TRACE;
	ret = gpio_get_value(newgpio_rb);
	printk("et200 gpio_rb  before write   rb pin = %d \n", ret);

	miscdev = (struct miscdevice *)(file->private_data);
	et200_dev = (struct veb_et200_data *)dev_get_drvdata(miscdev->this_device);
	mutex_lock(&(et200_dev->dev_lock));

	#ifdef ET200_SPI_USE_MMAP
	if (ET200_ALREADY_MAPPED == et200_dev->mmapped){
		tx_tmp = (unsigned char*)et200_dev->mmap_addr;
	}else
	#endif
	{
		if(copy_from_user(et200_dev->buffer, (const char __user *)buf, count))
			goto func_error;
		tx_tmp = (unsigned char*)et200_dev->buffer;
	}

	if(count < MAX_TRANSFER_LEN){
		left = count % 1024;
		length = count - left;
	}else if(count == MAX_TRANSFER_LEN){
		left = 0;
		length = MAX_TRANSFER_LEN;
	}else /*(count > MAX_TRANSFER_LEN)*/{
		ET200_SPI_ERR("et200_write data should not over 256K\n");
		goto func_error;
	}

	#ifdef SPI_MSG_DUMP
	ET200_SPI_ARRAY_WITH_PREFIX("et200_write dump buffer :", tx_tmp, count);
	#endif

	ret = et200_spi_wake(WAKE_TIME*5);
	if(0 != ret)
	{
		goto func_error;
	}

	spi_message_init(&p);
	
	if(length > 0){
		xfer.tx_buf     = tx_tmp,
		xfer.rx_buf     = rx_tmp,
		xfer.len        = length,
		xfer.speed_hz	= 1000000,
		xfer.cs_change  = 0,
		xfer.bits_per_word = BITS_PER_WORD,
		xfer.delay_usecs = 3,
		xfer.tx_nbits = SPI_NBITS_SINGLE;
		xfer.rx_nbits = SPI_NBITS_SINGLE;
		spi_message_add_tail(&xfer, &p);
	}

	if(left){
		tx_left = tx_tmp + length;
		xfer_left.tx_buf     = tx_left,
		xfer_left.rx_buf     = rx_left,
		xfer_left.len        = left,
		xfer_left.speed_hz	= 1000000,
		xfer_left.cs_change  = 0,
		xfer_left.bits_per_word = BITS_PER_WORD,
		xfer_left.delay_usecs = 3,
		xfer_left.tx_nbits = SPI_NBITS_SINGLE;
		xfer_left.rx_nbits = SPI_NBITS_SINGLE;
		spi_message_add_tail(&xfer_left, &p);
	}

	#ifdef SPI_MSG_DUMP
	ET200_SPI_INFO("et200_write: start sync\n");
	#endif

	spi_sync(et200_dev->spi, &p);

	#ifdef SPI_MSG_DUMP
	ET200_SPI_INFO("et200_write: sync end\n");
	#endif

	//et200_spi_send(et200_dev->spi, tx_tmp, count);  

	mutex_unlock(&(et200_dev->dev_lock));
	ET200_SPI_TRACE_OUT;
	return count;

func_error:
	mutex_unlock(&(et200_dev->dev_lock));
	ET200_SPI_ERR("veb_et200_write error\n");
	return 0;

}

#ifdef ET200_SPI_USE_MMAP
static int et200_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long phys;
	struct veb_et200_data *et200_dev = NULL;
	struct miscdevice *miscdev = NULL;
	ET200_SPI_TRACE;

	miscdev = (struct miscdevice *)(file->private_data);
	et200_dev = (struct veb_et200_data *)dev_get_drvdata(miscdev->this_device);
	mutex_lock(&(et200_dev->dev_lock));
	
	phys = virt_to_phys(et200_dev->mmap_addr);
	if(remap_pfn_range(vma,
						vma->vm_start,
						phys >> PAGE_SHIFT,
						vma->vm_end - vma->vm_start,
						vma->vm_page_prot)){
		ET200_SPI_ERR("et200_mmap error!\n");
		et200_dev->mmapped = ET200_NOT_MAPPED;
		mutex_unlock(&(et200_dev->dev_lock));
		return -1;
	}

	et200_dev->mmapped = ET200_ALREADY_MAPPED;
	mutex_unlock(&(et200_dev->dev_lock));
	ET200_SPI_TRACE_OUT;
	return 0;
}
#endif


static const struct file_operations et200_fops = {
	.owner = THIS_MODULE,
	.open  = et200_open,
	.unlocked_ioctl = et200_ioctl,
	.compat_ioctl = et200_ioctl,
	.read = et200_read,
	.write = et200_write,
#ifdef ET200_SPI_USE_MMAP
	.mmap = et200_mmap,
#endif
	.release = et200_release,
};

static struct miscdevice et200_miscdev = {
	MISC_DYNAMIC_MINOR,
	ET200_NAME,
	&et200_fops
};

static int et200_spi_probe(struct spi_device *spi)
{
	int ret = 0;
	struct veb_et200_data	 *et200_dev = NULL;
#ifdef ET200_SPI_USE_MMAP
	int i;
	int order = 0;
#endif
    struct device_node *dt = spi->dev.of_node;
    ET200_SPI_TRACE;

	et200_dev = kzalloc(sizeof(struct veb_et200_data), GFP_KERNEL);
	if (NULL == et200_dev)
	{
		ET200_SPI_ERR("et200_spi_probe spidev malloc error!\n");
		return -ENOMEM;
	}

    et200_dev->spi = spi;
	et200_dev->miscdev = &et200_miscdev;
	mutex_init(&(et200_dev->dev_lock));
	
	et200_dev->buffer = (unsigned char*)kzalloc(XFER_BUF_SIZE, GFP_KERNEL | GFP_DMA);
	if (!et200_dev->buffer) 
	{
		ET200_SPI_ERR("et200_spi_probe et200_dev.buffer malloc failed\n");
		ret = -ENOMEM;
		goto end;
	}
	

	
	et200_dev->mmapped = ET200_NOT_MAPPED;
#ifdef ET200_SPI_USE_MMAP
	mutex_init(&(et200_dev->mmap_lock));
	
	//reserve 2M buffer for mmap
	order = get_order(ET200_MMAP_SIZE);
	et200_dev->mmap_addr = (unsigned char *)__get_free_pages(GFP_KERNEL, order);		
	if(et200_dev->mmap_addr){
		ET200_SPI_INFO("et200_spi_probe kernel_memaddr:0x%lx  order:%d  PAGE_SIZE:%ld\n", (unsigned long)et200_dev->mmap_addr, order, PAGE_SIZE);
		for(i=0;i<ET200_MMAP_SIZE/PAGE_SIZE;i++)
			SetPageReserved(virt_to_page(et200_dev->mmap_addr + i*PAGE_SIZE));
	}else{
		ET200_SPI_ERR("et200_spi_probe membuffer malloc failed\n");
		ret = -ENOMEM;
		goto end;
	}
#endif
	spi_set_drvdata(spi, et200_dev);	
	
//	et200_set_spiport();	


    newgpio_rst = of_get_named_gpio(dt, "et200,rst-gpio", 0);
    if (!gpio_is_valid(newgpio_rst))
        printk(" DT:mydevdata->gpio_rst value is not valid\n");

    newgpio_rb = of_get_named_gpio(dt, "et200,rb-gpio", 0);
    if (!gpio_is_valid(newgpio_rb))
        printk(" DT:mydevdata->gpio_rb value is not valid\n");

    newgpio_wakeup = of_get_named_gpio(dt, "et200,wakeup-gpio", 0);
    if (!gpio_is_valid(newgpio_wakeup))
        printk(" DT:mydevdata->newgpio_wakeup value is not valid\n");
	ret = gpio_get_value(newgpio_rb);
	printk("et200 gpio_rb after set  rb pin = %d \n", ret);
	


//    et200_rst_gpio = devm_gpiod_get(&spi->dev,"et200rst",1);
//    if (IS_ERR(et200_rst_gpio)) {
//        pr_err("et200_rst_gpio gpio invalid\n");
//        return -EIO;
//    }
//    et200_rb_gpio = devm_gpiod_get(&spi->dev,"et200rb", GPIOD_IN);
//    if (IS_ERR(et200_rb_gpio)) {
//        pr_err("et200_rb_gpio gpio invalid\n");
//        return -EIO;
//    }		
//    gpiod_direction_input(et200_rb_gpio);	
//
    et200_en_gpio = devm_gpiod_get(&spi->dev,"et200en", GPIOD_OUT_HIGH);
    if (IS_ERR(et200_en_gpio)) {
        pr_err("et200_en_gpio gpio invalid\n");
        return -EIO;
    }		
    gpiod_direction_output(et200_en_gpio, 1);

	et200_set_gpio();
	ret = gpio_get_value(newgpio_rb);
	printk("et200 gpio_rb  after set  rb pin = %d \n", ret);
	
	spi->mode = SPI_MODE_3;
	spi->bits_per_word = BITS_PER_WORD;
	spi->max_speed_hz = 1000000;
	ret = spi_setup(spi);
	if(ret < 0)
	{
		ET200_SPI_ERR("et200_spi_probe  spidev spi_setup error!\n");
		ret = -1;
		goto end;
	}

	if (misc_register(&et200_miscdev))
	{
		ET200_SPI_ERR("et200_spi_probe %s: failed to register device\n", ET200_NAME);
		ret = -1;
		goto end;
	}
	dev_set_drvdata(et200_miscdev.this_device, et200_dev);
	ET200_SPI_INFO("et200_spi_probe %s: v%s\n", ET200_DESC, ET200_VERSION);
	
	
	ret = gpio_get_value(newgpio_rb);
	printk("et200 gpio_rb probe finish rb pin = %d \n", ret);
	
	ET200_SPI_TRACE_OUT;
	return ret;
end:
	if(NULL != et200_dev->buffer){
		kfree(et200_dev->buffer);
		et200_dev->buffer = NULL;
	}
	if (NULL != et200_dev){
		kfree(et200_dev);
		et200_dev = NULL;
	}
	return ret;
}

static int et200_spi_remove(struct spi_device *spi)
{
	struct veb_et200_data	 *et200_dev = NULL;
#ifdef ET200_SPI_USE_MMAP
	int i;
	int order = 0;
#endif
	ET200_SPI_TRACE;

	et200_dev = spi_get_drvdata(spi);

#ifdef ET200_SPI_USE_MMAP
	order = get_order(ET200_MMAP_SIZE);
	if(et200_dev->mmap_addr){
		for(i=0;i<ET200_MMAP_SIZE/PAGE_SIZE;i++)
			ClearPageReserved(virt_to_page(et200_dev->mmap_addr + i*PAGE_SIZE));
		free_pages((unsigned long)et200_dev->mmap_addr, order);
	}
	et200_dev->mmapped = ET200_NOT_MAPPED;
#endif
	
	if(NULL != et200_dev->buffer){
		kfree(et200_dev->buffer);
		et200_dev->buffer = NULL;
	}
	if(NULL != et200_dev){
		kfree(et200_dev);
		et200_dev = NULL;
	}


	ET200_SPI_TRACE_OUT;
	return 0;
}

static struct of_device_id et200_spi_table[] = {
	{.compatible = "et200,spi_et200",}, 
	{ },
};

struct spi_device_id spi_id_table_et200 = {"spi_et200", 0};
/*
static struct spi_board_info spi_board_devs[] __initdata = {
	[1] = {
	.modalias = "spi_et200",
	.bus_num = 3,
	.chip_select = 1,
	.mode = SPI_MODE_3,
	}
};
*/
static struct spi_driver et200_spi_driver = {
	.driver = {
		.name        = "spi_et200",
		.owner        = THIS_MODULE,
		.bus = &spi_bus_type,
		.of_match_table = et200_spi_table,
	},

	.probe        = et200_spi_probe,
	.remove        = et200_spi_remove,
	.id_table   = &spi_id_table_et200,
};

static int __init et200_spi_init(void)
{
	int rc = 0;

    printk("%s,%d\n",__func__,__LINE__);
//	spi_register_board_info(spi_board_devs, ARRAY_SIZE(spi_board_devs));
    printk("%s,%d\n",__func__,__LINE__);
	rc = spi_register_driver(&et200_spi_driver);
	if (rc < 0)
	{
		ET200_SPI_ERR("et200_spi register fail : %d\n", rc);
		return rc ;
	}

	return rc ;
}

static void __exit et200_spi_exit(void)
{
	if(et200_miscdev.this_device)
		misc_deregister(&et200_miscdev);

	spi_unregister_driver(&et200_spi_driver);

	return;
}



module_init(et200_spi_init);
module_exit(et200_spi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CCORE ET200S-T40 Software");
MODULE_DESCRIPTION("spi et200 driver ");
MODULE_VERSION("1.0");









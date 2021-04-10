extern void lcd_printf(const char *fmt, ...);

void __attribute__((weak)) fastboot_lcd_printf(void)
{
    lcd_printf("   fastboot mode");
    return;
}

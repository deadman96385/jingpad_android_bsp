#include<security/trustzone/trustzone.h>

void secure_sp_entry(unsigned long s_entry,unsigned long ns_entry)
{
	tos_entry(s_entry,ns_entry);
}

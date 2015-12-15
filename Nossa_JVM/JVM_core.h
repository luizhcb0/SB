#include "macros.h"

void jvmStartup(u1 *classPathStr, int flag);

void initializeClass(ClassFile *class_ptr);

u2 seekMethodInClass(ClassFile *class_ptr, char *methName_str, char *methDescriptor_str);

int findClass(char* ClassName);

u2 findCode(method_info *method);

void createFrame(method_info *method, ClassFile *Class);

void deleteFrame();

void callMethod(ClassFile *class_ptr, char *mth_name, char *mth_descriptor);


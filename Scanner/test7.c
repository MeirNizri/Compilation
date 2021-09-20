struct Books {
   char  title[50];
   int   book_id;
};
struct Books Book1;
strcpy( Book1.title, "C Programming");
struct Books *struct_pointer;
struct_pointer = &Book1;
struct_pointer->title;


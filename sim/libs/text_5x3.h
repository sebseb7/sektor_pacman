#ifndef TEXT_5x3_H_
#define TEXT_5x3_H_

void print_5x3_at (int x, int y, char *text, unsigned char r, unsigned char g, unsigned char b);
void putc_5x3_at (int x, int y, char text, unsigned char r, unsigned char g, unsigned char b);
void print_num_5x3_at (int x, int y, int number, int length, int pad, unsigned char r, unsigned char g, unsigned char b);
void print_unsigned_5x3_at (int x, int y, unsigned int number, int length, char pad, unsigned char r, unsigned char g, unsigned char b);

#endif

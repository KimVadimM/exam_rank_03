#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

char *draw;
float x, y, rad;
char type, color, back;
int w, h;

int check_hit(float i, float j)
{
    float dist = sqrtf((i - x) * (i - x) + (j - y) * (j - y));

    if (dist <= rad)
    {
        if (dist - rad <= -1)
            return(1);
        return(2);
    }
    return (0);
}


void drawing(void)
{
    int i = -1;
    int j;
    int hit;
    while (++i < w)
    {
        j = -1;
        while (++j < h)
        {
            hit = check_hit((float)i, (float)j);
            if ((hit == 2) || (hit == 1 && type == 'C'))
                draw[i + j * w] = color;
        }
    }
}


int parcer(FILE *file)
{
    int i = 0;
    int result;
    
    if (fscanf(file, "%d %d %c\n", &w, &h, &back) != 3)
        return (1);
    if (w < 1 || w > 300 || h < 1 || h > 300)
        return (1);
    draw = malloc(w * h);
    while (i < w * h)
    {
        draw[i++] = back;
    }
    while ((result = fscanf(file, "%c %f %f %f %c\n", &type, &x, &y, &rad, &color)) == 5)
    {
        if (rad < 0 || (type != 'c' && type != 'C'))
            return (1);
        drawing();      
    }
    if (result != -1)
        return (1);
    return (0);
}

void ft_output(void)
{
    int i = -1;
    while (++i < h)
    {
        write(1, draw + i * w, w);
        write(1, "\n", 1);
    }
}



int main (int argc, char **argv)
{
    FILE *file;
    if (argc != 2)
    {
        write(1, "Error: argumnet\n", 16);
		return (1);
    }
    if (!(file = fopen(argv[1], "r")) || parcer(file))
    {
        write(1, "Error: Operation file corrupted\n", 32);
		return (1);
    }
    ft_output();
    fclose(file);
    free(draw);
    return (0);
}
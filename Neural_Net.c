#include "gifenc.h"
#include <stdio.h>
#include <stdlib.h>


struct img
{
    /*Imagen con su etiqueta*/
    int label;
    int data[28*28];
};

struct neuron
{
    /*Neurona que contiene el id, el tipo, su entrada, la salida activada*/
    int id;
    char type;
    double n_value;
    double activated;
};

struct n_link
{
    /*Enlace neuronal con id, su conexion y el valor que transporta*/
    int id;
    int from;
    int to;
    double l_value;
};

struct a_i
{
    /*Inteligencia artificial(esto se debe guardar en un archivo)*/
    struct neuron input[28];
    struct neuron hidden[19];/*Promedio de la entrada y la salida*/
    struct neuron output[10];
    struct n_link l[(28*19)+(19*10)];/*Enlaces para todas las neuronas*/
};

struct img get_next_img(FILE* images, FILE* labels)
{
    /*Esta funcion obtiene la siguiente imagen en el archivo*/
    struct img next_img;
    int c, w, h, c2;
    h = 28;//Altura de la imagen
    w = 28;//Anchura de la imagen
    next_img.label = fgetc(labels);
    printf("Numero: %d\n", next_img.label);
    for (c = 0; c < (h*w); c++)
    {
        //Almacenar la imagen
        next_img.data[c] = fgetc(images);
    }
    //Esta parte muestra una vista previa de la imagen con su etiqueta
    for (c = 0; c < h; c++)
    {
        for (c2 = 0; c2 < w; c2++)
        {
            if (next_img.data[c2 + 28*c] < 75)
            {
                printf("_");
            }
            else if (next_img.data[c2 + 28*c] > 150)
            {
                printf("#");
            }
            else
            {
                printf("0");
            }
        }
        printf("\n");
    }
    return next_img;
}

void giffy_img(char name[80], int iterable[28*28])
{
    /*Funcion que crea un gif*/
    int j;
    char nname[80];
    strcpy(nname, name);
    strcat(nname, ".gif");
    ge_GIF *gif = ge_new_gif( nname,  /* Nombre de archivo */
        28, 28,           /* Tamano del archivo */
        (uint8_t []) {  /* paleta de colores(grises) */
            0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFD, 0xFD, 0xFD,
            0xFC, 0xFC, 0xFC, 0xFB, 0xFB, 0xFB, 0xFA, 0xFA, 0xFA,
            0xF9, 0xF9, 0xF9, 0xF8, 0xF8, 0xF8, 0xF7, 0xF7, 0xF7,
            0xF6, 0xF6, 0xF6, 0xF5, 0xF5, 0xF5, 0xF4, 0xF4, 0xF4,
            0xF3, 0xF3, 0xF3, 0xF2, 0xF2, 0xF2, 0xF1, 0xF1, 0xF1,
            0xF0, 0xF0, 0xF0, 0xEF, 0xEF, 0xEF, 0xEE, 0xEE, 0xEE,
            0xED, 0xED, 0xED, 0xEC, 0xEC, 0xEC, 0xEB, 0xEB, 0xEB,
            0xEA, 0xEA, 0xEA, 0xE9, 0xE9, 0xE9, 0xE8, 0xE8, 0xE8,
            0xE7, 0xE7, 0xE7, 0xE6, 0xE6, 0xE6, 0xE5, 0xE5, 0xE5,
            0xE4, 0xE4, 0xE4, 0xE3, 0xE3, 0xE3, 0xE2, 0xE2, 0xE2,
            0xE1, 0xE1, 0xE1, 0xE0, 0xE0, 0xE0, 0xDF, 0xDF, 0xDF,
            0xDE, 0xDE, 0xDE, 0xDD, 0xDD, 0xDD, 0xDC, 0xDC, 0xDC,
            0xDB, 0xDB, 0xDB, 0xDA, 0xDA, 0xDA, 0xD9, 0xD9, 0xD9,
            0xD8, 0xD8, 0xD8, 0xD7, 0xD7, 0xD7, 0xD6, 0xD6, 0xD6,
            0xD5, 0xD5, 0xD5, 0xD4, 0xD4, 0xD4, 0xD3, 0xD3, 0xD3,
            0xD2, 0xD2, 0xD2, 0xD1, 0xD1, 0xD1, 0xD0, 0xD0, 0xD0,
            0xCF, 0xCF, 0xCF, 0xCE, 0xCE, 0xCE, 0xCD, 0xCD, 0xCD,
            0xCC, 0xCC, 0xCC, 0xCB, 0xCB, 0xCB, 0xCA, 0xCA, 0xCA,
            0xC9, 0xC9, 0xC9, 0xC8, 0xC8, 0xC8, 0xC7, 0xC7, 0xC7,
            0xC6, 0xC6, 0xC6, 0xC5, 0xC5, 0xC5, 0xC4, 0xC4, 0xC4,
            0xC3, 0xC3, 0xC3, 0xC2, 0xC2, 0xC2, 0xC1, 0xC1, 0xC1,
            0xC0, 0xC0, 0xC0, 0xBF, 0xBF, 0xBF, 0xBE, 0xBE, 0xBE,
            0xBD, 0xBD, 0xBD, 0xBC, 0xBC, 0xBC, 0xBB, 0xBB, 0xBB,
            0xBA, 0xBA, 0xBA, 0xB9, 0xB9, 0xB9, 0xB8, 0xB8, 0xB8,
            0xB7, 0xB7, 0xB7, 0xB6, 0xB6, 0xB6, 0xB5, 0xB5, 0xB5,
            0xB4, 0xB4, 0xB4, 0xB3, 0xB3, 0xB3, 0xB2, 0xB2, 0xB2,
            0xB1, 0xB1, 0xB1, 0xB0, 0xB0, 0xB0, 0xAF, 0xAF, 0xAF,
            0xAE, 0xAE, 0xAE, 0xAD, 0xAD, 0xAD, 0xAC, 0xAC, 0xAC,
            0xAB, 0xAB, 0xAB, 0xAA, 0xAA, 0xAA, 0xA9, 0xA9, 0xA9,
            0xA8, 0xA8, 0xA8, 0xA7, 0xA7, 0xA7, 0xA6, 0xA6, 0xA6,
            0xA5, 0xA5, 0xA5, 0xA4, 0xA4, 0xA4, 0xA3, 0xA3, 0xA3,
            0xA2, 0xA2, 0xA2, 0xA1, 0xA1, 0xA1, 0xA0, 0xA0, 0xA0,
            0x9F, 0x9F, 0x9F, 0x9E, 0x9E, 0x9E, 0x9D, 0x9D, 0x9D,
            0x9C, 0x9C, 0x9C, 0x9B, 0x9B, 0x9B, 0x9A, 0x9A, 0x9A,
            0x99, 0x99, 0x99, 0x98, 0x98, 0x98, 0x97, 0x97, 0x97,
            0x96, 0x96, 0x96, 0x95, 0x95, 0x95, 0x94, 0x94, 0x94,
            0x93, 0x93, 0x93, 0x92, 0x92, 0x92, 0x91, 0x91, 0x91,
            0x90, 0x90, 0x90, 0x8F, 0x8F, 0x8F, 0x8E, 0x8E, 0x8E,
            0x8D, 0x8D, 0x8D, 0x8C, 0x8C, 0x8C, 0x8B, 0x8B, 0x8B,
            0x8A, 0x8A, 0x8A, 0x89, 0x89, 0x89, 0x88, 0x88, 0x88,
            0x87, 0x87, 0x87, 0x86, 0x86, 0x86, 0x85, 0x85, 0x85,
            0x84, 0x84, 0x84, 0x83, 0x83, 0x83, 0x82, 0x82, 0x82,
            0x81, 0x81, 0x81, 0x80, 0x80, 0x80, 0x7F, 0x7F, 0x7F,
            0x7E, 0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7C, 0x7C, 0x7C,
            0x7B, 0x7B, 0x7B, 0x7A, 0x7A, 0x7A, 0x79, 0x79, 0x79,
            0x78, 0x78, 0x78, 0x77, 0x77, 0x77, 0x76, 0x76, 0x76,
            0x75, 0x75, 0x75, 0x74, 0x74, 0x74, 0x73, 0x73, 0x73,
            0x72, 0x72, 0x72, 0x71, 0x71, 0x71, 0x70, 0x70, 0x70,
            0x6F, 0x6F, 0x6F, 0x6E, 0x6E, 0x6E, 0x6D, 0x6D, 0x6D,
            0x6C, 0x6C, 0x6C, 0x6B, 0x6B, 0x6B, 0x6A, 0x6A, 0x6A,
            0x69, 0x69, 0x69, 0x68, 0x68, 0x68, 0x67, 0x67, 0x67,
            0x66, 0x66, 0x66, 0x65, 0x65, 0x65, 0x64, 0x64, 0x64,
            0x63, 0x63, 0x63, 0x62, 0x62, 0x62, 0x61, 0x61, 0x61,
            0x60, 0x60, 0x60, 0x5F, 0x5F, 0x5F, 0x5E, 0x5E, 0x5E,
            0x5D, 0x5D, 0x5D, 0x5C, 0x5C, 0x5C, 0x5B, 0x5B, 0x5B,
            0x5A, 0x5A, 0x5A, 0x59, 0x59, 0x59, 0x58, 0x58, 0x58,
            0x57, 0x57, 0x57, 0x56, 0x56, 0x56, 0x55, 0x55, 0x55,
            0x54, 0x54, 0x54, 0x53, 0x53, 0x53, 0x52, 0x52, 0x52,
            0x51, 0x51, 0x51, 0x50, 0x50, 0x50, 0x4F, 0x4F, 0x4F,
            0x4E, 0x4E, 0x4E, 0x4D, 0x4D, 0x4D, 0x4C, 0x4C, 0x4C,
            0x4B, 0x4B, 0x4B, 0x4A, 0x4A, 0x4A, 0x49, 0x49, 0x49,
            0x48, 0x48, 0x48, 0x47, 0x47, 0x47, 0x46, 0x46, 0x46,
            0x45, 0x45, 0x45, 0x44, 0x44, 0x44, 0x43, 0x43, 0x43,
            0x42, 0x42, 0x42, 0x41, 0x41, 0x41, 0x40, 0x40, 0x40,
            0x3F, 0x3F, 0x3F, 0x3E, 0x3E, 0x3E, 0x3D, 0x3D, 0x3D,
            0x3C, 0x3C, 0x3C, 0x3B, 0x3B, 0x3B, 0x3A, 0x3A, 0x3A,
            0x39, 0x39, 0x39, 0x38, 0x38, 0x38, 0x37, 0x37, 0x37,
            0x36, 0x36, 0x36, 0x35, 0x35, 0x35, 0x34, 0x34, 0x34,
            0x33, 0x33, 0x33, 0x32, 0x32, 0x32, 0x31, 0x31, 0x31,
            0x30, 0x30, 0x30, 0x2F, 0x2F, 0x2F, 0x2E, 0x2E, 0x2E,
            0x2D, 0x2D, 0x2D, 0x2C, 0x2C, 0x2C, 0x2B, 0x2B, 0x2B,
            0x2A, 0x2A, 0x2A, 0x29, 0x29, 0x29, 0x28, 0x28, 0x28,
            0x27, 0x27, 0x27, 0x26, 0x26, 0x26, 0x25, 0x25, 0x25,
            0x24, 0x24, 0x24, 0x23, 0x23, 0x23, 0x22, 0x22, 0x22,
            0x21, 0x21, 0x21, 0x20, 0x20, 0x20, 0x1F, 0x1F, 0x1F,
            0x1E, 0x1E, 0x1E, 0x1D, 0x1D, 0x1D, 0x1C, 0x1C, 0x1C,
            0x1B, 0x1B, 0x1B, 0x1A, 0x1A, 0x1A, 0x19, 0x19, 0x19,
            0x18, 0x18, 0x18, 0x17, 0x17, 0x17, 0x16, 0x16, 0x16,
            0x15, 0x15, 0x15, 0x14, 0x14, 0x14, 0x13, 0x13, 0x13,
            0x12, 0x12, 0x12, 0x11, 0x11, 0x11, 0x10, 0x10, 0x10,
            0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0D, 0x0D, 0x0D,
            0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A,
            0x09, 0x09, 0x09, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07,
            0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04,
            0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
            0x00, 0x00, 0x00

        },
        8,              /* profundidad de paleta == log2(# de colores) */
        0               /* bucle infinito */
    );
    for (j = 0; j < (28*28); j++)
    {
        gif->frame[j] = iterable[j];
    }
    ge_add_frame(gif, 1);
    ge_close_gif(gif);
}

int save_ai(struct a_i* ai, char filename[80])
{
    /*Esta funcion guarda el estado de la IA para poder seguirla usando*/
    FILE *out;
    char joinit[100];
    strcpy(joinit, filename);
    strcat(joinit, ".dat");
    out = fopen(joinit, "wb");
    fwrite(ai, sizeof(ai), 1, out);
    fclose(out);
    return 0;
}

void load_ai(struct a_i* ai, char filename[80])
{
    /*Esta funcion carga la IA desde un archivo*/
    FILE* in;
    char joinit[100];
    strcpy(joinit, filename);
    in = fopen(joinit, "rb");
    fread(ai, sizeof(ai), 1, in);
    fclose(in);
}

int ai_guess(struct a_i* ai)
{

}

double train_ai(struct a_i* ai,FILE* images, FILE* labels, int n_of_times)
{
    /*Esta funcion entrena la red neuronal por x veces*/
    int i;
    int count = {sizeof(ai->input)/sizeof(ai->input[0])};
    int stop;
    struct img current_img;
    for (stop = 0; stop < n_of_times; stop++)
    {
        printf("Iteracion n.%d\n", stop);
        current_img = get_next_img(images, labels);
        for (int i = 0; i < count; ++i)
        {
            /* Llevar la siguiente imagen a la entrada */
            ai->input[i].n_value = current_img.data[i];
        }
    }
    return 0;
}

int init_ai(struct a_i* ai)
{
    /*Esta funcion inicializa una IA con valores aleatorios en sus componentes*/
    int c;//Contador que voy a reusar
    int n_of_inp = {sizeof(ai->input)/sizeof(ai->input[0])};
    int n_of_hid = {sizeof(ai->hidden)/sizeof(ai->hidden[0])};
    int n_of_out = {sizeof(ai->output)/sizeof(ai->output[0])};
    int n_of_links = {sizeof(ai->l)/sizeof(ai->l[0])};
    double rand_1_n1;//Variable de numero aleatorio
    for (int c = 0; c < n_of_inp; ++c)
    {
        ai->input[c].id = c+1;
        ai->input[c].type = 'i';
    }
    for (int c = 0; c < n_of_hid; ++c)
    {
        //Generar un valor aleatorio entre 1 y -1
        rand_1_n1 = -1 + (2*((double)rand() / (double)RAND_MAX));
        ai->hidden[c].id = c+1;
        ai->hidden[c].n_value = rand_1_n1;
        ai->input[c].type = 's';
        printf("Guardar en hidden %i %5.14f\n", c+1, rand_1_n1);
    }
    for (int c = 0; c < n_of_out; ++c)
    {
        //Generar un valor aleatorio entre 1 y -1
        rand_1_n1 = -1 + (2*((double)rand() / (double)RAND_MAX));
        ai->output[c].id = c+1;
        ai->output[c].n_value = rand_1_n1;
        ai->input[c].type = 'r';
        printf("Guardar en outputs %i %5.14f\n", c+1, rand_1_n1);
    }
    return 0;
}

int main()
{
    FILE *tr_images, *tr_labels; //Pointers para los archivos
    tr_labels = fopen("train-labels.idx1-ubyte", "rb");
    tr_images = fopen("train-images.idx3-ubyte", "rb");
    int i;
    for (i = 0; i < 16; i++)
    {
        //Saltarme el encabezado de imagenes(ya se que es)
        fgetc(tr_images);
    }
    for (int i = 0; i < 8; ++i)
    {
        //Saltar encabezado de etiquetas
        fgetc(tr_labels);
    }

    /*struct img testing;
    testing = get_next_img(tr_images, tr_labels);
    giffy_img("lol", testing.data);*/
    struct a_i aitest, new_ai;
    init_ai(&aitest);
    printf("%4.5f\n", aitest.input[1].n_value);
    save_ai(&aitest,"KnCriGno");
    printf("%4.5f\n", aitest.input[0].n_value);
    load_ai(&new_ai, "KnCriGno.dat");
    printf("%4.5f\n", new_ai.input[0].n_value);
    train_ai(&aitest, tr_images, tr_labels, 2);

    //CleanAfterCooking
    fclose(tr_labels);
    fclose(tr_images);
    system("PAUSE");
}

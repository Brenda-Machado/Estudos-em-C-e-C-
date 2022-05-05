// questionário de fundamentos do C

typedef struct {
    float x, y;
} ponto_t;

ponto_t q = {23.0, 27.0};
ponto_t* p = &q;

q.x = q.y = p->x *= 2;

// questão de identificar anos bissextos
// Todo valor igual a zero é considerado false, e todo valor diferente de zero é considerado true.
int x = 2015;
    if (x > 0) {
//return !(x % 400) || ((x % 100) && !(x%4));
//return x % 400 == 0 || (x % 100 && x % 4 == 0);
//return (x % 400 == 0 || x % 100) && x % 4 == 0;
return (!(x % 400) || (x % 100)) && !(x%4);
    }
    if (x % 4 == 0) {
        if (x % 100) return -1;
        else if (!(x % 400)) return 1;
        return 0;
}
//
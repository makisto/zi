#include <list>
#include <vector>
#include <sstream>
#include <Windows.h>
#include "LibSignes.h"

using namespace std;

void print_vector(int* vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << vector[i] << " ";
    }
    cout << endl << endl;
}

void print_graph(int** g, int n, int *vertex_size)
{
    for (int i = 0; i < n; i++)
    {
        cout << "VERTEX " << i + 1 << ": ";
        for (int j = 0; j < vertex_size[i]; j++)
        {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int check_izomorph_graph(int n, int** g, int** f, int* vertex_size, int* p, int* f_vertex_size)
{
    int ret = 0;
    bool is_true = true;
    int** restore_graph = new int* [n];
    int* restore_vertex_size = new int[n];

    cout << "GRAPH G - " << endl;
    print_graph(g, n, vertex_size);

    cout << "GRAPH F - " << endl;
    print_graph(f, n, f_vertex_size);

    for (int i = 0; i < n; i++)
    {
        restore_vertex_size[p[i] - 1] = vertex_size[i];
        restore_graph[p[i] - 1] = new int[restore_vertex_size[p[i] - 1]];
        for (int k = 0; k < restore_vertex_size[p[i] - 1]; k++)
        {
            restore_graph[p[i] - 1][k] = p[g[i][k] - 1];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < restore_vertex_size[i]; j++)
        {
            if (f[i][j] != restore_graph[i][j])
            {
                is_true = false;
                break;
            }
        }
    }
    if (is_true == false)
    {
        ret = -4;
        goto finally;
    }

    cout << "RESTORE GRAPH F - " << endl;
    print_graph(restore_graph, n, restore_vertex_size);

    finally:
        return ret;
}

int check_hamilton_cycle(int **f, int* f_vertex_size, int* hamilton_cycle_f, int n)
{
    int i = 0;
    int ret = 0;
    bool is_true_cycle;

    cout << "GRAPH F - " << endl;
    print_graph(f, n, f_vertex_size);

    cout << "HAMILTON CYCLE FOR GRAPH F:" << endl;
    print_vector(hamilton_cycle_f, n);

    while (i < n - 1)
    {
        is_true_cycle = false;
        for (int j = 0; j < f_vertex_size[hamilton_cycle_f[i] - 1]; j++)
        {
            if (f[hamilton_cycle_f[i] - 1][j] == hamilton_cycle_f[i + 1])
            {
                i++;
                is_true_cycle = true;
                break;
            }
        }
        if (is_true_cycle == false)
        {
            ret = -5;
            goto finally;
        }
    }

    finally:
        return ret;
}

int hamilton(int **a, int* c, int* path, int n, int k, int v0)
{
    int v, q1 = 0;
    for (v = 0; v < n && !q1; v++)
    {
        if (a[v][path[k - 1]] || a[path[k - 1]][v])
        {
            if (k == n && v == v0)
            {
                q1 = 1;
            }
            else if (c[v] == -1)
            {
                c[v] = k; 
                path[k] = v;
                q1 = hamilton(a, c, path, n, k + 1, v0);
                if (!q1)
                {
                    c[v] = -1;
                }
            }
            else
            {
                continue;
            }
        }
    }   
    return q1;
}

int main(void)
{
    srand(time(NULL));

    int n = 0;
    int v0 = 7;
    int ret = 0;
    int vertex = 0;
    int counter = 0;
    int buf_counter = 0;

    int** g;
    int* vertex_size;
    int* hamilton_cycle;

    int** f;
    int* f_vertex_size;
    int* hamilton_cycle_f;

    int* c;
    int* p;
    int** matrix;

    int tmp;
    int choose;
    int rand_index1;
    int rand_index2 ;

    int vertex_buf[1000] = { 0 };

    LibSignes cryptograph;

    string s;
    stringstream ss;
    ifstream fin("graph.txt");
    if (fin.good())
    {
        getline(fin, s);
        ss << s;
        ss >> n;
        c = new int[n];
        p = new int[n];
        g = new int* [n];
        matrix = new int* [n];
        vertex_size = new int[n];
        hamilton_cycle = new int[n];
        for (int i = 0; i < n; i++)
        {
            vertex_size[i] = 0;
        }
        ss.clear();
        while (!fin.eof())
        {
            getline(fin, s);
            ss << s;
            /*if (n == counter)
            {
                int j = 0;
                while (ss >> vertex)
                {
                    hamilton_cycle[j] = vertex;
                    j++;
                }
            }
            else
            {*/
                while (ss >> vertex)
                {
                    vertex_size[counter]++;
                    vertex_buf[buf_counter] = vertex;
                    buf_counter++;
                }
                g[counter] = new int[buf_counter];
                for (int j = 0; j < buf_counter; j++)
                {
                    g[counter][j] = vertex_buf[j];
                }
                counter++;
                ss.clear();
                buf_counter = 0;
            //}
        }
        if (n != counter)
        {
            cout << "WRONG DATA" << endl;
            ret = -2;
            goto finally;
        }
    }
    else
    {
        cout << "NO FILE" << endl;
        ret = -1;
        goto finally;
    }

    for (int j = 0; j < n; j++)
    {
        matrix[j] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < vertex_size[i]; j++)
        {
            matrix[i][g[i][j] - 1] = 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        c[i] = -1;
    }
    c[v0 - 1] = v0 - 1;
    hamilton_cycle[0] = v0 - 1;

    if (hamilton(matrix, c, hamilton_cycle, n, 1, v0 - 1))
    {
        for (int i = 0; i < n; i++)
        {
            hamilton_cycle[i]++;
        }
    }
    else
    {
        cout << "NO HAMILTON CYCLE!" << endl;
        ret = -10;
        goto finally;
    }

    for (int i = 0; i < n; i++)
    {
        p[i] = i + 1;
    }

    cout << "GRAPH G - " << endl;
    print_graph(g, n, vertex_size);

    cout << "HAMILTON CYCLE FOR GRAPH G - " << endl;
    print_vector(hamilton_cycle, n);

    for(int t = 0; t < 10; t++)
    {
        cout << "ITERATION " << t + 1 << ": " << endl;

        f = new int* [n];
        f_vertex_size = new int[n];
        hamilton_cycle_f = new int[n];
        for (int i = 0; i < n; i++) 
        {
            rand_index1 = rand() % n;
            rand_index2 = rand() % n;

            tmp = p[rand_index1];
            p[rand_index1] = p[rand_index2];
            p[rand_index2] = tmp;
        }

        for (int i = 0; i < n; i++)
        {
            f_vertex_size[p[i] - 1] = vertex_size[i];
            f[p[i] - 1] = new int[f_vertex_size[p[i] - 1]];
            for (int k = 0; k < f_vertex_size[p[i] - 1]; k++)
            {
                f[p[i] - 1][k] = p[g[i][k] - 1];
            }
            hamilton_cycle_f[i] = p[hamilton_cycle[i] - 1];
        }

        cout << "P:" << endl;
        print_vector(p, n);

        choose = rand() % 2 + 1;
        switch (choose)
        {
            case 1:
                cout << "1 - IS F ISOMORPH TO G? " << endl;
                Sleep(3000);

                ret = check_izomorph_graph(n, g, f, vertex_size, p, f_vertex_size);

                if (0 != ret)
                {
                    cout << "GRAPHS ARE NOT EQUALS!" << endl;
                    ret = -5;
                    goto finally;
                }
                else
                {
                    cout << "GRAPHS ARE EQUALS!" << endl;
                }
                break;
            case 2:
                cout << "2 - GIVE ME HAMILTON CYCLE" << endl;
                Sleep(3000);

                ret = check_hamilton_cycle(f, f_vertex_size, hamilton_cycle_f, n);

                if (0 != ret)
                {
                    cout << "CYCLE IS NOT CORRECT!" << endl;
                    ret = -6;
                    goto finally;
                }
                else
                {
                    cout << "CYCLE IS CORRECT!" << endl;
                }
                break;
        }
    }

    finally:
        return ret;
}



















































////////////BLIND SIGN////////////////////
/*struct open_database
{
    int yes = 0;
    int no = 0;
    int abandon = 0;
}database;

long long p = 0;

long long f(long long n, long long N)
{
    return cryptograph.left_right_fast_pow_by_module(n, p - 3, p);
}

long long *server_generate(
    long long *const c)
{
    srand(time(NULL));

    long long q = 0;
    long long g = 0;
    long long o = 0;
    long long d = 0;

    long long* u = new long long[3];
    long long* client_settings = new long long[2];

    do
    {
        cryptograph.prime_number_count(&p, &q, &g, 20);
    } while (p == q);

    client_settings[0] = p * q;

    o = (p - 1) * (q - 1);

    cout << "P - " << p << endl << "Q - " << q << endl << "N - " << client_settings[0] << endl << "O - " << o << endl << endl;

    for (;;)
    {
        *c = (rand() * rand() + rand()) % 1000000000;
        u = cryptograph.abstract_gcd(*c, o);
        if (1 == u[0])
        {
            client_settings[1] = u[1];
            if (client_settings[1] < 0)
            {
                client_settings[1] += o;
            }
            if (1 == (*c * client_settings[1]) % o)
            {
                break;
            }
        }
    }
    cout << "C - " << *c << endl << "D - " << client_settings[1] << endl << endl;

    return client_settings;
}

void server_confirmed(long long n, long long s, long long d, long long N)
{
    int byte = 0;
    cout << "SERVER CONFIRMED:" << endl << "n - " << n << endl << "S - " << s << endl << "D - " << d << endl << "N - " << N << endl << endl;
    if (f(n, N) == cryptograph.left_right_fast_pow_by_module(s, d, N))
    {
        cout << cryptograph.left_right_fast_pow_by_module(s, d, N) << endl;
        cout << "CONFIRM. CLIENT VOTE IS ";
        byte = (n >> 32) & 1;
        if (1 == byte)
        {
            database.yes++;
            cout << "YES" << endl;
        }
        else
        {
            byte = (n >> 33) & 1;
            if (1 == byte)
            {
                database.abandon++;
                cout << "ABANDON" << endl;
            }
            else
            {
                database.no++;
                cout << "NO" << endl;
            }
        }
    }
    else
    {
        cout << "NOT CONFIRM" << endl;
    }
}

long long server_marking(long long n1, long long c, long long N)
{
    cout << "SERVER MARKING:" << endl << "N1 - " << n1 << endl << "c - " << c << endl << "N - " << N << endl;
    long long s1 = cryptograph.left_right_fast_pow_by_module(n1, c, N);
    cout << "S1 - " << s1 << endl << endl;

    return s1;
}

long long client_confirmed(long long s1, long long r1, long long N)
{
    cout << "CLIENT CONFIRMED:" << endl << "S1 - " << s1 << endl << "r1 - " << r1 << endl << "N - " << N << endl;
    long long s = ((s1 % N) * (r1 % N)) % N;
    cout << "S - " << s << endl << endl;

    return s;
}

void client_voting(
    long long *const client_message,
    long long *client_settings,
    long long *const n1,
    long long *const r1)
{
    long long v = 0;
    bool is_confirmed = false;
    cout << "CLIENT VOTING:" << endl;
    
    while (!is_confirmed)
    {
        cout << "YOUR VOTE: Yes - 1, No - 0, Abandon - 2" << endl;
        cin >> v;
        if (1 != v && 2 != v && 0 != v)
        {
            cout << "TRY AGAIN" << endl;
        }
        else
        {
            is_confirmed = true;
        }
    }

    long long r = 0;
    long long rnd = (rand() * rand() + rand()) % 4294967296;

    *client_message = rnd | (v * 4294967296);
    long long* u = new long long[3];

    cout << "n - " << *client_message << endl << endl;

    for (;;)
    {
        r = (rand() * rand() + rand()) % (client_settings[0] - 2) + 2;
        u = cryptograph.abstract_gcd(r, client_settings[0]);
        if (1 == u[0])
        {
            *r1 = u[1];
            if (*r1 < 0)
            {
                *r1 += client_settings[0];
            }
            break;
        }
    }
    cout << "r - " << r << endl << "r1 - " << *r1 << endl << endl;

    cout << "F(n) - " << f(*client_message, client_settings[0]) << endl << endl;

    *n1 = ((f(*client_message, client_settings[0]) % client_settings[0]) * cryptograph.left_right_fast_pow_by_module(r, client_settings[1], client_settings[0])) % client_settings[0];
    cout << "n1 - " << *n1 << endl << endl;
}

int main(void)
{
    long long r1 = 0;
    long long client_sign = 0;
    long long client_message = 0;
    long long server_secret_key = 0;
    long long client_marking_key = 0;
    long long* client_settings = new long long[2];

    client_settings = server_generate(&server_secret_key);

    for (int i = 0; i < 10; i++)
    {
        client_voting(&client_message, client_settings, &client_marking_key, &r1);

        server_confirmed
        (
            client_message,
            client_confirmed
            (
                server_marking
                (
                    client_marking_key,
                    server_secret_key,
                    client_settings[0]),
                r1,
                client_settings[0]
            ),
            client_settings[1],
            client_settings[0]
        );
    }

    cout << database.yes << " " << database.no << " " << database.abandon << endl;
}*/

    ///////////MENTAL POKER////////////////
    /*typedef enum
    {
        CARDS = 52,
        PLAYERS = 5,
        CARDS_TO_TABLE = 5,
        CARDS_TO_PLAYER = 2,
        CHECK_CARDS = CARDS_TO_TABLE + (CARDS_TO_PLAYER * PLAYERS)
    } poker_settings;
    if (CHECK_CARDS > CARDS)
    {
        cout << "INCORRECT DATA - TOO MUCH CARDS" << endl;
        return -1;
    }

    int main(void)
    {
        srand(time(NULL));

        long long p = 0;
        long long q = 0;
        long long g = 0;

        LibSignes cryptograph;

        string visual[CARDS] =
        {
            "2 Hearts", "3 Hearts", "4 Hearts", "5 Hearts", "6 Hearts", "7 Hearts", "8 Hearts", "9 Hearts", "10 Hearts", "Jack of Hearts", "Queen of Hearts", "King of Hearts",  "Ace of Hearts",
            "2 Diamonds", "3 Diamonds", "4 Diamonds", "5 Diamonds", "6 Diamonds", "7 Diamonds", "8 Diamonds", "9 Diamonds", "10 Diamonds", "Jack of Diamonds", "Queen of Diamonds", "King of Diamonds", "Ace of Diamonds",
            "2 Spades", "3 Spades", "4 Spades", "5 Spades", "6 Spades", "7 Spades", "8 Spades", "9 Spades", "10 Spades", "Jack of Spades", "Queen of Spades", "King of Spades", "Ace of Spades",
            "2 Cross", "3 Cross", "4 Cross", "5 Cross", "6 Cross", "7 Cross", "8 Cross", "9 Cross", "10 Cross", "Jack of Cross", "Queen of Cross", "King of Cross", "Ace of Cross"
        };

        map <int, string> dictionary;

        long long c[PLAYERS] = { 0 };
        long long d[PLAYERS] = { 0 };
        long long* u = new long long[3];
        long long cyphro_cards[CARDS][2]{};
        long long encrypted_cards[CARDS][2] = {};
        long long cards[PLAYERS][CARDS_TO_PLAYER]{};
        long long table_cards[CARDS_TO_TABLE] = { 0 };

        for (int i = 1; i <= CARDS; i++)
        {
            dictionary.insert(make_pair(i, visual[i - 1]));
        }

        do
        {
            cryptograph.prime_number_count(&p, &q, &g, 20);
        } while (p < CARDS);

        cout << "P - " << p << endl;

        for (int i = 0; i < PLAYERS; i++)
        {
            label1:
                c[i] = (rand() * rand() + rand()) % (p - 2) + 1;
                u = cryptograph.abstract_gcd(c[i], p - 1);
                if (1 == u[0])
                {
                    d[i] = u[1];
                    if (d[i] < 0)
                    {
                        d[i] += p - 1;
                    }
                }
                else
                {
                    goto label1;
                }
                if (1 != cryptograph.left_right_fast_pow_by_module(c[i] * d[i], 1, p - 1))
                {
                    goto label1;
                }
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            cout << i + 1 << " PLAYER: Ci - " << c[i] << " Di - " << d[i] << endl;
        }

        cout << "CYPHRO CARDS:" << endl;
        for (int i = 0; i < CARDS; i++)
        {
            cyphro_cards[i][0] = static_cast<long long>(i) + 1;
            cyphro_cards[i][1] = (rand() * rand() + rand()) % (p - 2) + 1;
            encrypted_cards[i][0] = cyphro_cards[i][0];
            encrypted_cards[i][1] = cyphro_cards[i][1];

            cout << dictionary[cyphro_cards[i][0]] << "----" << cyphro_cards[i][1] << endl;
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            cout << endl << "PLAYER " << i + 1 << ":ENCRYPTED CARDS BEFORE SHUFFLE:" << endl;
            for (int j = 0; j < CARDS; j++)
            {
                encrypted_cards[j][1] = cryptograph.left_right_fast_pow_by_module(encrypted_cards[j][1], c[i], p);
                cout << dictionary[encrypted_cards[j][0]] << "----" << encrypted_cards[j][1] << endl;
            }

            for (int k = 0; k < CARDS; k++)
            {
                int z1 = rand() % CARDS;
                int z2 = rand() % CARDS;
                long long temp = encrypted_cards[z1][0];
                long long temp1 = encrypted_cards[z1][1];
                encrypted_cards[z1][0] = encrypted_cards[z2][0];
                encrypted_cards[z1][1] = encrypted_cards[z2][1];
                encrypted_cards[z2][0] = temp;
                encrypted_cards[z2][1] = temp1;
            }

            cout << endl << "PLAYER " << i + 1 << ":ENCRYPTED CARDS AFTER SHUFFLE:" << endl;
            for (int i = 0; i < CARDS; i++)
            {
                cout << dictionary[encrypted_cards[i][0]] << "----" << encrypted_cards[i][1] << endl;
            }
        }

        int k = 0;
        for (int i = 0; i < PLAYERS; i++)
        {
            for (int j = 0; j < CARDS_TO_PLAYER; j++)
            {
                cards[i][j] = encrypted_cards[k][1];
                k++;
            }
        }

        for (int i = 0; i < CARDS_TO_TABLE; i++)
        {
            table_cards[i] = encrypted_cards[k][1];
            k++;
        }

        for (int i = 0; i < PLAYERS; i++)
        {
            for (int j = 0; j < PLAYERS; j++)
            {
                for (int k = 0; k < CARDS_TO_PLAYER; k++)
                {
                    if (i != j)
                    {
                        cards[i][k] = cryptograph.left_right_fast_pow_by_module(cards[i][k], d[j], p);
                    }
                }
            }
            cout << endl << "PLAYER " << i + 1 << ": DECODE CARDS:" << endl;
            for (int k = 0; k < CARDS_TO_PLAYER; k++)
            {
                cards[i][k] = cryptograph.left_right_fast_pow_by_module(cards[i][k], d[i], p);
                cout << cards[i][k] << endl;
            }
            cout << endl;

            for (int j = 0; j < CARDS_TO_TABLE; j++)
            {
                table_cards[j] = cryptograph.left_right_fast_pow_by_module(table_cards[j], d[i], p);
            }
        }

        cout << endl << "TABLE CARDS: DECODE CARDS:" << endl;
        for (int i = 0; i < CARDS_TO_TABLE; i++)
        {
            cout << table_cards[i] << endl;
        }
        cout << endl;

        for (int i = 0; i < PLAYERS; i++)
        {
            for (int j = 0; j < CARDS_TO_PLAYER; j++)
            {
                for (int k = 0; k < CARDS; k++)
                {
                    if (cards[i][j] == cyphro_cards[k][1])
                    {
                        cards[i][j] = cyphro_cards[k][0];
                    }
                }
            }

            for (int i = 0; i < CARDS_TO_TABLE; i++)
            {
                for (int j = 0; j < CARDS; j++)
                {
                    if (table_cards[i] == cyphro_cards[j][1])
                    {
                        table_cards[i] = cyphro_cards[j][0];
                    }
                }
            }
        }

        cout << "CARDS:" << endl << endl;
        for (int i = 0; i < PLAYERS; i++)
        {
            cout << "PLAYER " << i + 1 << ":" << endl;
            for (int j = 0; j < CARDS_TO_PLAYER; j++)
            {
                cout << dictionary[cards[i][j]] << endl;
            }
            cout << endl << endl;
        }

        cout << "TABLE CARDS:" << endl << endl;
        for (int i = 0; i < CARDS_TO_TABLE; i++)
        {
            cout << dictionary[table_cards[i]] << endl;
        }
        cout << endl;
    }*/

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

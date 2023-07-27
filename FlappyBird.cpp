#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <cmath>
/// Struct do vectora
typedef struct point {
	int x, y;
}point;

///ustawianie koloru białego
ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
///ustawianie koloru zielonego
ALLEGRO_COLOR col = al_map_rgb(0, 255, 0);
///ustawianie koloru niebieskiego
ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
///ustawianie koloru zielonego
ALLEGRO_COLOR green = al_map_rgb(0, 254, 0); 

#define oknoszerokosc  1080
#define oknowysokosc  720

ALLEGRO_BITMAP* bitmapa;

/// <summary>
/// Funkcja w ktorej iniciowana jest biblioteka oraz inne przydatne funckje typu klawiatura mysz obrazy itp.
/// </summary>
void init() {
	if (!al_init()) {
		std::cout << "nie udało się zainiciować biblioteki allegro" << std::endl;
	}
	al_init_image_addon(); /// do zdjec 
	al_init_primitives_addon(); /// iniciuje prymitywy 
	al_install_keyboard(); ///iniciuje klawiature
	al_install_mouse(); ///iniciuje mysz
	
}
/// <summary>
/// klasa PrimitiveRender
/// </summary>
class PrimitiveRender {
public:
	/// <summary>
	/// Funkcja ta odpowiada za rysowanie prymitywów lini poziomej,pionowej,prostokąta oraz wypełn
	/// </summary>
	void Primitywki() {
		//niebieska pionowa linia
		al_draw_line(100, 100, 200, 100, blue, 1);
		//niebeiska pozioma linia
		al_draw_line(150, 150, 150, 250, blue, 1);
		// niebieski pomalowany prostokat
		al_draw_filled_rectangle(170, 170, 270, 270, blue);
		// niebieski nie pomalowany prostokat
		al_draw_rectangle(200, 200, 300, 300, blue, 1);
	};
	/// <summary>
	/// Funckja umożliwia rysowanie przyrostowe
	/// </summary>
	/// <param name="x0">punkt x</param>
	/// <param name="y0">punkt y</param>
	/// <param name="x1">punkt x1</param>
	/// <param name="y1">punkt x2</param>
	void Przyrostowe(int x0, int y0, int x1, int y1){
		// Przyrostowe
		
		float dx, dy, m;

		dx = x1 - x0;
		dy = y1 - y0;
		m = dy / dx;

		//Jeżeli m< 1 to rysujemy linię po osi x, w przeciwnym wypadku po y
		if (abs(m) < 1) {
			//Sprawdzamy czy trzeba zamienić argumenty tak, aby rysowanie następowało od mniejszego do większego
			if (x0 > x1) {
				float tmp = x0;
				x0 = x1;
				x1 = tmp;
				tmp = y0;
				y0 = y1;
				y1 = tmp;
			}

			//linia pionowa
			if (dx == 0) {
				for (int y = y0; y <= y1; y++)
					al_put_pixel(x0, y, col);
				return;
			}

			dx = x1 - x0;
			dy = y1 - y0;
			m = dy / dx;

			float y = y0;
			for (int x = x0; x <= x1; x++) {
				al_put_pixel(x, int(y + 0.5), col);
				y += m;
			}
		}
		else {
			//Sprawdzamy czy trzeba zamienić argumenty tak, aby rysowanie następowało od mniejszego do większego
			if (y0 > y1) {
				float tmp = x0;
				x0 = x1;
				x1 = tmp;
				tmp = y0;
				y0 = y1;
				y1 = tmp;
			}

			if (dx == 0) {
				for (int y = y0; y <= y1; y++)
					al_put_pixel(x0, y, col);
				return;
			}

			dx = x1 - x0;
			dy = y1 - y0;
			m = dx / dy;

			float x = x0;
			for (int y = y0; y <= y1; y++) {
				al_put_pixel(int(x + 0.5), y, col);
				x += m;
			}
		}
		
	}
	/// <summary>
	/// funkcja opdowiada za rysowanie punktu / pixela
	/// </summary>
	/// <param name="x">wspolrzedna X punktu </param>
	/// <param name="y">wspolrzedna Y punktu </param>
	void punkt(int x, int y) {

		al_draw_pixel(x, y, white);
	}
	/// <summary>
	/// Funkcja odpowiada za rysowanie lini
	/// </summary>
	/// <param name="x1">wspolrzedna X1 punktu</param>
	/// <param name="y1">wspolrzedna Y1 punktu</param>
	/// <param name="x2">wspolrzedna X2 punktu</param>
	/// <param name="y2"wspolrzedna Y2 punktu></param>
	void linia(int x1, int y1,int x2, int y2) {

		al_draw_line(x1, y1, x2, y2, white, 1);
	}
	/// <summary>
	/// Funkcja odpowiada za rysowanie lini lamanej
	/// </summary>
	/// <param name="x1">wspolrzedna X1 punktu</param>
	/// <param name="y1">wspolrzedna y1 punktu</param>
	/// <param name="x2">wspolrzedna x2 punktu</param>
	/// <param name="y2">wspolrzedna y2 punktu</param>
	/// <param name="x3">wspolrzedna x3 punktu</param>
	/// <param name="y3">wspolrzedna y3 punktu</param>
	void linia_lamana(int x1, int y1, int x2, int y2, int x3, int y3) {

		al_draw_line(x1, y1, x2, y2, white, 1);
		al_draw_line(x2, y2, x3, y3, white, 1);
	}
	/// <summary>
	/// Funkcja odpowiada za rysowanie lini lamej zamknietej
	/// </summary>
		/// <param name="x1">wspolrzedna X1 punktu</param>
	/// <param name="y1">wspolrzedna y1 punktu</param>
	/// <param name="x2">wspolrzedna x2 punktu</param>
	/// <param name="y2">wspolrzedna y2 punktu</param>
	/// <param name="x3">wspolrzedna x3 punktu</param>
	/// <param name="y3">wspolrzedna y3 punktu</param>
	void linia_lamana_zamknieta(int x1, int y1, int x2, int y2, int x3, int y3) {

		al_draw_line(x1, y1, x2, y2, white, 1);
		al_draw_line(x2, y2, x3, y3, white, 1);
		al_draw_line(x3, y3, x1, y1, white, 1);
	}
	/// <summary>
	/// Funckja odpowiadająca za rysowanie kola
	/// </summary>
	/// <param name="x">wspolrzedna x</param>
	/// <param name="y">wspolrzedna y</param>
	/// <param name="r">promien </param>
	void kolo(int x, int y, int r) {
		int x1, y1;

		for (double i = 0; i <= 3.1415 / 4; i += 1.0 / (2 * r)) {
			x1 = r * cos(i);
			y1 = r * sin(i);
			al_put_pixel(x + x1, y + y1, al_map_rgb(255, 255, 255));
			al_put_pixel(x + y1, y + x1, al_map_rgb(255, 255, 255));
			al_put_pixel(x - y1, y + x1, al_map_rgb(255, 255, 255));
			al_put_pixel(x - x1, y + y1, al_map_rgb(255, 255, 255));
			al_put_pixel(x - x1, y - y1, al_map_rgb(255, 255, 255));
			al_put_pixel(x - y1, y - x1, al_map_rgb(255, 255, 255));
			al_put_pixel(x + y1, y - x1, al_map_rgb(255, 255, 255));
			al_put_pixel(x + x1, y - y1, al_map_rgb(255, 255, 255));
		}
	}
	/// <summary>
	/// Funkcja opdowiada za rysowanie elipsy 
	/// </summary>
	/// <param name="x">wspolrzedna x</param>
	/// <param name="y">wspolrzedna Y</param>
	/// <param name="r1">promien r1</param>
	/// <param name="r2">promien r2</param>
	void elipsa(int x, int y, int r1, int r2) {
		int x1, y1;

		for (double i = 0; i <= 3.1415 / 2; i += 1.0 / (2 * r2)) {
			x1 = r1 * cos(i);
			y1 = r2 * sin(i);
			al_put_pixel(x + x1, y + y1, al_map_rgb(255, 255, 255));
			al_put_pixel(x - x1, y + y1, al_map_rgb(255, 255, 255));
			al_put_pixel(x - x1, y - y1, al_map_rgb(255, 255, 255));
			al_put_pixel(x + x1, y - y1, al_map_rgb(255, 255, 255));
		}
	}
	/// <summary>
	/// Funkcja odpowiedziala za wypelnianie figury
	/// </summary>
	/// <param name="x">wspolrzedna x</param>
	/// <param name="y">wspolrzedna y</param>
	/// <param name="bitmapa">obszar bitmapy na ktorym bedzie uzupelniala </param>
	void wypelnij(int x, int y, ALLEGRO_BITMAP* bitmapa)
	{
		std::vector <point> p;

		p.push_back({ x, y });

		while (p.size() > 0) {
			point npoint = p.back();
			p.pop_back();

			ALLEGRO_COLOR kolor = al_get_pixel(bitmapa, npoint.x, npoint.y);
			unsigned char r1, g1, b1, r2,g2,b2,r3,g3,b3;
			al_unmap_rgb(kolor, &r1, &g1, &b1);
			al_unmap_rgb(white, &r2, &g2, &b2);
			al_unmap_rgb(green, &r3, &g3, &b3);

			if ((r1 == r2 && g1 == g2 && b1 == b2 ) && (r1 != r3 && g1 != g3 && b1 != b3))
			{
				al_put_pixel(npoint.x, npoint.y, al_map_rgb(0, 0, 0));

				p.push_back({ npoint.x - 1, npoint.y });
				p.push_back({ npoint.x + 1, npoint.y });
				p.push_back({ npoint.x, npoint.y - 1 });
				p.push_back({ npoint.x, npoint.y + 1 });
			}
		}
	}
};

/// <summary>
/// Klasa point2D
/// </summary>
class Point2D {
	PrimitiveRender primitiverender;

public:
	int a, b;
	/// <summary>
	/// metoda odczytujaca wspolrzedne
	/// </summary>
	/// <param name="a">wspolrzedna x</param>
	/// <param name="b">wspolrzedna y</param>
	void odczytaj(int a, int b) {
		std::cout << a << "," << b << std::endl;
	}
	/// <summary>
	/// metoda ktora modyfikuje wspolrzedne
	/// </summary>
	/// <param name="a1">wspolrzedna x po modyfikacji</param>
	/// <param name="b1">wspolrzedna y po modyfikacji </param>
	void modyfikuj(int a1, int b1) {
		a = a1;
		b = b1;
	}
	/// <summary>
	/// funckja rysujaca punkt
	/// </summary>
	void rysuj() {
		modyfikuj(a,b);

		primitiverender.punkt(a,b);
	}
	/// <summary>
	/// metoda rysujaca linie 
	/// </summary>
	void rysujlnie() {
		primitiverender.Primitywki();
	}
	/// <summary>
	/// metoda wykorzystujaca translacje 
	/// </summary>
	/// <param name="tx">wspolrzedna x po translacji</param>
	/// <param name="ty">wspolrzedna y po transalcji </param>
	void translacja(int tx,int ty) {
		int x2 = a + tx;
		int y2 = b + ty;
		primitiverender.punkt(x2, y2);
	}
	/// <summary>
	/// metoda rotujaca linje 
	/// </summary>
	/// <param name="x1">wspolrzedna x1</param>
	/// <param name="y1">wspolrzedna x2</param>
	void rotacja(int x1, int y1) {
		int x2 = a + (x1 - a) * cos(30) - (y1 - b) * sin(30);
		int y2 = b + (x1 - a) * sin(30) - (y1 - b) * cos(30);
		primitiverender.linia(a,b,x2,y2);
	}
};
/// <summary>
/// Klasa linesegment zawiera w sobie metody do rysowania lini
/// </summary>
class LineSegment {
	PrimitiveRender primitiverender;
public: 
	int x1, y1, x2, y2;
	/// <summary>
	/// funckja odczytujaca wspolrzedne 
	/// </summary>
	/// <param name="x1">wspolrzedna x1</param>
	/// <param name="y1">wspolrzedna y1</param>
	/// <param name="x2">wspolrzedna x2</param>
	/// <param name="y2">wspolrzedna y2</param>
	void odczytaj(int x1, int y1, int x2, int y2) {
		std::cout << x1 << "," << y2 << ":" << x2 << "," << y2 << std::endl;
	}
	/// <summary>
	/// Funckja modyfikujaca wspolrzedne 
	/// </summary>
	/// <param name="a1">wspolrzedna x1</param>
	/// <param name="b1">wspolrzedna y1</param>
	/// <param name="a2">wspolrzedna x2</param>
	/// <param name="b2">wspolrzedna y2</param>
	void modyfikuj(int a1, int b1, int a2,int b2) {
		x1 = a1;
		y1 = b1;
		x2 = a2;
		y2 = b2;
	}
	/// <summary>
	/// Funckja rysujaca linie 
	/// </summary>
	void rysuj() {
		modyfikuj(x1, y1,x2,y2);

		primitiverender.linia(x1, y1, x2, y2);
	}

	/// <summary>
	/// funckja rysujaca linie lamana 
	/// </summary>
	/// <param name="x1">wspolrzedna x1</param>
	/// <param name="y1">wspolrzedna y1</param>
	/// <param name="x2">wspolrzedna x2</param>
	/// <param name="y2">wspolrzedna y2</param>
	/// <param name="x3">wspolrzedna x3</param>
	/// <param name="y3">wspolrzedna y3</param>
	void rysuj_linia_lamana(int x1, int y1, int x2, int y2, int x3, int y3) {
		primitiverender.linia_lamana(x1,y1,x2,y2,x3,y3);
	}
	/// <summary>
	/// funkcja rysujaca linie lamana ale zamknieta
	/// </summary>
	/// <param name="x1">wspolrzedna x1</param>
	/// <param name="y1">wspolrzedna y1</param>
	/// <param name="x2">wspolrzedna x2</param>
	/// <param name="y2">wspolrzedna y2</param>
	/// <param name="x3">wspolrzedna x3</param>
	/// <param name="y3">wspolrzedna y3</param>
	void rysuj_linia_lamana_zamknieta(int x1, int y1, int x2, int y2, int x3, int y3) {
		primitiverender.linia_lamana_zamknieta(x1, y1, x2, y2, x3, y3);
	}
	/// <summary>
	/// funkcja odpowiedzialna za rotacje lini
	/// </summary>
	/// <param name="x1">wspolrzedna x</param>
	/// <param name="y1">wspolrzedna y</param>
	void rotacja(int x1, int y1) {
		int x2 = x1 + (x1 - x1) * cos(30) - (y1 - y1) * sin(30);
		int y2 = y1 + (x1 - x1) * sin(30) - (y1 - y1) * cos(30);
		primitiverender.linia(x1, y1, x2, y2);
	}

};
/// <summary>
/// klasa gameobjecy
/// </summary>
class GameObject {
	/// <summary>
	/// abstarkcyjna metoda jump
	/// </summary>
	void jump();
	/// <summary>
	/// abstarkcyjna metoda kolizja
	/// </summary>
	void kolizja();
	/// <summary>
	/// abstarkcyjna metoda score
	/// </summary>
	void score();
	/// <summary>
	/// abstarkcyjna metoda tablica
	/// </summary>
	void tablica();
	/// <summary>
	/// abstarkcyjna metoda opadanie
	/// </summary>
	void opdanie();
};
/// <summary>
/// klasa UpdatableObject
/// </summary>
class UpdatableObject {
	/// <summary>
	/// abstarkcyjna metoda update
	/// </summary>
	void update();
};
/// <summary>
/// Klasa DrawableObject
/// </summary>
class DrawableObject {
	void draw();
};
/// <summary>
/// Klasa TransformableObject
/// </summary>
class TransformableObject {
	/// <summary>
	/// abstrakcyjna metoda translate
	/// </summary>
	void translate();
	/// <summary>
	/// abstrakcyjna metoda rotate
	/// </summary>
	void rotate();
	/// <summary>
	/// abstrakcyjna metoda scale
	/// </summary>
	void scale();
};
/// <summary>
/// Klasa shapeobject dziedziczaca DrawableObject, TransformableObject
/// </summary>
class ShapeObject:public DrawableObject, TransformableObject {
};
/// <summary>
/// klasa player 
/// </summary>
class Player {
public:
	/// <summary>
	/// metoda ruch zawierajaca ruch
	/// </summary>
	void ruch() {
		int x1 = 50;
		int y1 = 50;
		int x2 = 100;
		int y2 = 100;
		al_draw_filled_rectangle(x1, y1, x2, y2, blue);
	}
};


/// <summary>
/// glowna czesc programu odpowiedzialna za uruchomienie wszelkich funkcji oraz zawiera nieskonczona petle w ktorej dziala gra
/// </summary>
/// <returns>zwraca wynik</returns>
int main() {
	init();
	
	PrimitiveRender primitivereader;
	Point2D point;
	LineSegment line;
	Player player;

	point.odczytaj(10, 5);
	point.modyfikuj(650, 650);

	line.odczytaj(500,500,600,600);
	line.modyfikuj(700, 700, 900, 700);


	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY* display = al_create_display(oknoszerokosc, oknowysokosc); //tworzenie okna wyświetlającego.
	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 0, ALLEGRO_SWAP_METHOD); //ustawianie bufforowania na podwójne 
	al_set_window_title(display, "Flappy Bird");
	
	bitmapa = al_create_bitmap(600, 600);
	al_set_target_bitmap(bitmapa);
	al_clear_to_color(white);
	al_set_target_bitmap(al_get_backbuffer(display));



	ALLEGRO_BITMAP* ptak = NULL;
	ptak = al_load_bitmap("skok.png");




	ALLEGRO_BITMAP* ptak2 = NULL;
	ptak2 = al_load_bitmap("2.png");
	





	if (!display) {
		std::cout << "nie udało się tworzenie okna " << std::endl;
	}
	

	

	// zmienne do gry 
	enum Direction { UP, DOWN }; // określa co ptak ma robić w danym momencie
	const float FPS = 60;  // ustawia częstotliowść odświeżania 
	bool draw = true; // ustawia rysowanie na wartość true aby 1 frame został naryswoany wraz z startem programu
	bool end = false; // zakańcza działanie programu ustawione na true zamyka okno
	float x = 100; //ustawia położenie birda w poziomie
	float y = 350; //ustawia położenie birda w pionioe
	int skok = DOWN;  // domyślnie ustawia ptaka na odadanie
	bool random = true;
	bool kolizja = false;
	bool add = false;
	int x1 = 1020;
	int y1 = 0;
	int i = 0;
	int score = 0;
	int z = 0;

	//std::default_random_engine generator;
	//std::uniform_real_distribution<double> los(100, 580);
	//int r1 = los(generator);
	srand(time(0));
	int r1[100];
	int r2;
	int j = 0;

	int x2 = 1020;
	int y2 = 720;


	
	// iniciacja potrzebnych rzeczy

	

	//rejestracja eventów 
	ALLEGRO_TIMER* timer = timer = al_create_timer(1.0 / FPS);  //ustawia timer na odświeżanie 60 klatek na sekunde 
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue(); // inicjacia kolejki zdarzeń
	al_register_event_source(event_queue, al_get_keyboard_event_source()); // rejestracja zdarzeń z klawiatury
	al_register_event_source(event_queue, al_get_mouse_event_source()); // rejestracja zdarzeń z myszy
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); // rejestracja zdarzeń z timera 



	// al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer); //wystartowanie timera aby gra chodziła w 60 fpsach
	while (!end)
		//pętla głowna gry
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);


		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			end = true;
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE: end = true; break;
			case ALLEGRO_KEY_SPACE: //podskocz flappy birdem;
			case ALLEGRO_KEY_UP:
				skok = UP;
				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				skok = DOWN;
				break;
			}
		}

		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			//eventy myszki
		}

		else if (y <= 0) {
		//	al_show_native_message_box(display, "koniec", "przegrana", " ptak wyleciał poza mape", NULL, NULL);
		//	end = true;  kolizja chwilowo wykomentowana na potrzeby wizualizacji silnika
		}

		else if (y >= 720) {
		//	al_show_native_message_box(display, "koniec", "przegrana", "ptak uderzył w ziemie", NULL, NULL);
			//end = true;  kolizja chwilowo wykomentowana na potrzeby wizualizacji silnika
		}

		if (x1 < 150 && x1>100) {
			if (y<r1[j] || y>r2) {
				//kolizja = true; kolizja chwilowo wykomentowana na potrzeby wizualizacji silnika
			}
		}
		if (kolizja == true) {
			al_show_native_message_box(display, "koniec", "przegrana", "ptak uderzył w rure", NULL, NULL);
			end = true;
		}


		if (add == true) {
			score++;
			add = false;
		}


		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			switch (skok)
			{
			case UP:
				y -= 5;
				//skok = DOWN;
				al_draw_bitmap(ptak, x, y, NULL);
				break;

			case DOWN:
				y += 2;
				al_draw_bitmap(ptak2, x, y, NULL);
				break;

			}
			draw = true;
		}

		if (random) {
			if (i < 100) {
				r1[i] = (rand() % 570) + 100;
				i++;
				random = false;
			}
			if (i > 100) {
				i = 0;
				random = false;
			}

		}
		if (draw) {
			draw = false;
			random = true;
				//starcik bitmapki
			/*al_set_target_bitmap(bitmapa);
			
			
			al_clear_to_color(white);
			al_draw_rectangle(200, 200, 300, 300, green, 1);
		//	primitivereader.wypelnij(250, 250, bitmapa);  // wypelnianie na czarny kolor figury 
			
			
			al_set_target_bitmap(al_get_backbuffer(display));
			al_draw_bitmap(bitmapa, 0, 0, 0);
			//endzik bitmapki 
			*/

			//primitivereader.Primitywki(); // rysowanie prymitywow lnia/ prostokat/prostokat zamalowny
			

			//primitivereader.kolo(50, 50, 10); //rysowanie kola
			//primitivereader.elipsa(100, 100, 10, 15); // rysowanie elipsy
			
			//point.rysuj(); // rysowanie punktu
			//point.translacja(50, 50);
			//line.rysuj(); // rysowanie lini
			//point.rotacja(700, 700);
			//line.rotacja(350, 550);

			//line.rysuj_linia_lamana(250,250,350,350,250,450); // rysowanie lini łamanej
			//line.rysuj_linia_lamana_zamknieta(250, 250, 350, 350, 250, 450); // rysowanie lini łamanej zamkniętej
			//primitivereader.Przytosowe(500,500,600,600); // rysowanie przyrostowe 

			//player.ruch();

			//al_draw_rectangle(x, y, x + 10, y + 10,green,1);
			

			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			al_draw_rectangle(x1, y1, x1 - 50, r1[j], green, 2.0);
			r2 = r1[j] + 100;
			al_draw_rectangle(x2, y2, x2 - 50, r2, green, 2.0);
			x1 -= 5;
			x2 -= 5;


			if (x1 <= 50) {
				j++;
				x1 = 1020;
				x2 = 1020;
				add = true;

			}
			if (j >= 100) {
				j = 0;
			}
		}

	}


	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return score;
};

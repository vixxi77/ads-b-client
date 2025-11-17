#include <raylib.h>
#include <stdio.h>

const int SCREEN_WIDTH  = 1000;
const int SCREEN_HEIGHT = 1000;

static int previous_x;
static int previous_y;

static float zoom = 1.0f;
float *pzoom = &zoom;


const double LITHUANIA_VERTEX[] = {26.494331495883756,55.615106919977634,26.58827924979039,55.16717560487167,25.7684326514798,54.84696259217509,25.536353794056993,54.28242340760253,24.450683628037037,53.905702216194754,23.48412763844985,53.91249766704114,23.24398725758951,54.22056671814914,22.731098667092652,54.327536932993326,22.65105187347254,54.582740993866736,22.75776370615526,54.85657440858138,22.315723504330577,55.015298570365864,21.268448927503467,55.190481675835315,21.055800408622417,56.031076361711065,22.201156853939494,56.33780182557949,23.878263787539964,56.27367137310527,24.86068444184076,56.37252838807963,25.000934279080894,56.16453074810484,25.533046502390334,56.100296942766036,26.494331495883756,55.615106919977634};

 

void draw_lt(const double *_lithuania_vertex, int count, int *previous_x, int *previous_y, float _zoom){

	const double minLon = 20.9;
	const double maxLon = 26.8;
	const double minLat = 53.9;
	const double maxLat = 56.45;

	float lonCenter = (minLon + maxLon) * 0.5;
	float latCenter = (minLat + maxLat) * 0.5;
	float lonSpan = (maxLon - minLon) * _zoom;
	float latSpan = (maxLat - minLat) * _zoom;
	float zoomMinLon = lonCenter - lonSpan * 0.5;
	float zoomMaxLon = lonCenter + lonSpan * 0.5;
	float zoomMinLat = latCenter - latSpan * 0.5;
	float zoomMaxLat = latCenter + latSpan * 0.5;

	for(int i = 0; i < count; i+=2){
		double longtitude = _lithuania_vertex[i];
		double latitude = _lithuania_vertex[i + 1];
		int x = (int)(((longtitude - zoomMinLon) / (zoomMaxLon - zoomMinLon)) * SCREEN_WIDTH);
		int y = (int)(((zoomMaxLat - latitude) / (zoomMaxLat - zoomMinLat)) * SCREEN_HEIGHT);
		DrawCircle(x, y, 1, RED);
		printf("x: %d, y: %d \n", x, y);
		if(i == 0){
			*previous_x = x;
			*previous_y = y;
		}  
		DrawLine(*previous_x, *previous_y, x, y, WHITE);
		*previous_x = x;
		*previous_y = y;
	}
}

int main(){

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Europe");
	SetTargetFPS(30);
	
	while(!WindowShouldClose()){
		if(IsKeyDown(KEY_UP)) *pzoom *= 1.1f;
		if(IsKeyDown(KEY_DOWN)) *pzoom *= 0.9f;
		BeginDrawing();
		ClearBackground(BLACK);
		draw_lt(LITHUANIA_VERTEX, sizeof(LITHUANIA_VERTEX) / sizeof(double), &previous_x, &previous_y, *pzoom);
		EndDrawing();
	}
	
	CloseWindow();

	return 0;
}

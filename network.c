#include <curl/curl.h>

int main(){
	CURL *hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(hnd, CURLOPT_URL, "https://api.adsb.lol/v2/lat/55.5/lon/24.5/dist/150");

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "accept: application/json");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

	CURLcode ret = curl_easy_perform(hnd);
	return 0;
}

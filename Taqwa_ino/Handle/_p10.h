#pragma once
#include <DMDESP.h>
#include <fonts/System6x7.h>
#include <fonts/EMSansSP8x16.h>
#include <fonts/Mono5x7.h>
#include <JWS_Ephemeris.h> // <-- Tambahkan baris ini

// Deklarasi variabel eksternal
extern DMDESP Disp;
extern int Data_Jam, Data_Menit, Data_Detik;
extern String teksBesar;
extern JWS_Ephemeris jws;

// Fungsi menampilkan jam utama
void RestoreWaktu();
void TampilkanLayoutUtama();
void TampilkanTeksBesar();

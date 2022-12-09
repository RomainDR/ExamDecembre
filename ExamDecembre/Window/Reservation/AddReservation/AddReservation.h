#pragma once
#include <windows.h>
#include <tchar.h>
#include <string>
#include "../../../Singleton/Singleton.h"
#include "../../../Reservation/Reservation.h"
#include <codecvt>


#pragma warning(disable: 4996)


#define ID_SAVE 1
#define ID_SHOW 2
class AddReservation
{
private:
    static void AddButton(const std::wstring& _title, const int& posX, const int& posY, const int& _width, const int& _heigth, HWND _window, const int id)
    {
        HWND Create = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed
            _title.c_str(),      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            posX,         // x position 
            posY,         // y position 
            _width,        // Button width
            _heigth,        // Button height
            _window,     // Parent window
            (HMENU) id,       // No menu.
            (HINSTANCE)GetWindowLongPtr(_window, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
    }

    // Fonction de rappel de la fenêtre
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        int separator = 50;
        int old = 10;

        // Récupération des données utilisateur (pointeur vers l'objet MyWindow)
        AddReservation* win = reinterpret_cast<AddReservation*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        // Traitement des messages de la fenêtre
        switch (uMsg)
        {
        case WM_CREATE:
            //TODO déplacer dans une autre class
            CreateWindow(TEXT("static"), TEXT("First Name: "), WS_VISIBLE | WS_CHILD, 5, old, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD, 200, old, 200, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("static"), TEXT("Last Name: "), WS_VISIBLE | WS_CHILD, 5, old + separator, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD, 200, old + separator, 200, 20, hwnd, NULL, NULL, NULL);
            old += separator;
            CreateWindow(TEXT("static"), TEXT("Number of peoples: "), WS_VISIBLE | WS_CHILD, 5, old + separator, 150, 20, hwnd, NULL, NULL, NULL);
            CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_BORDER | WS_CHILD, 200, old + separator, 200, 20, hwnd, NULL, NULL, NULL);

            AddButton(L"Sauvegarder", 10, 500, 100, 20, hwnd, 1);
            AddButton(L"Afficher", 200, 500, 100, 20, hwnd, 2);


            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
            case ID_SAVE:
                //TODO ajout de la réservation
                break;
            case ID_SHOW:
                std::vector<Reservation*> reservations = Singleton::GetInstance()->GetReservation();
                const int _size = reservations.size();
                for (int i = 0; i < _size; i++)
                {
                    Reservation res = *reservations.at(i);
                    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
                    std::wstring wstr = converter.from_bytes(res.ToString());
                    MessageBox(hwnd, wstr.c_str(), L"Title", MB_OK);
                }
                break;
            }
            break;
        case WM_CLOSE:
            if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
                exit(0);
            }
            // Else: User canceled. Do nothing.
            return 0;
        }
        // Appel de la fonction de rappel par défaut
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
public:
    AddReservation() {
        //Nom de la classe
        const wchar_t CLASS_NAME[] = L"Sample Window Class";


        //Struct qui va stocker les infos suivants
        WNDCLASS wc = { };
        HINSTANCE hInstance = HINSTANCE();
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;

        //Enregistre la "classe" de la struct
        if (!RegisterClass(&wc))
        {
            MessageBox(NULL,
                _T("Call to RegisterClassEx failed!"),
                _T("Error"),
                NULL);
            return;
        }


        /*Crée une fenetre avec un style optionnel, le nom de notre class, le titre de la fenetre, le style de la fenetre,
        une taille et position, la fenetre parent, un menu, l'instance de notre console, et data d'applications
        */
        HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"Hotel Réservation",           // Window text
            WS_OVERLAPPEDWINDOW,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            NULL,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );



        //on check si la window n'est pas null
        if (hwnd == NULL)
        {
            return;
        }


        HMENU menu = CreateMenu();

        //On affiche la window avec les commande
        ShowWindow(hwnd, 1);

        // Correct.

        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0) > 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    
};


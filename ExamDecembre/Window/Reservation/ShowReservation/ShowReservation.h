#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include "../../../Singleton/Singleton.h"
#include "../../../Reservation/Reservation.h"

class ShowReservation
{
private:
    // Fonction de rappel de la fenêtre
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        int separator = 50;
        int old = 10;
        // Récupération des données utilisateur (pointeur vers l'objet MyWindow)
        ShowReservation* win = reinterpret_cast<ShowReservation*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        // Traitement des messages de la fenêtre
        switch (uMsg)
        {
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
    ShowReservation() {
        //Nom de la classe
        const wchar_t CLASS_NAME[] = L"ShowRes";


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

        int posX = 10;
        int posY = 10;
        const int separator = 10;
        std::vector<Reservation*> reservations = Singleton::GetInstance()->GetReservation();
        const int _size = reservations.size();
        for (int i = 0; i < _size; i++)
        {
            Reservation _res = *reservations.at(i);
            std::string name = _res.GetName();
            std::wstring temp(name.length(), L' ');
            std::copy(name.begin(), name.end(), temp.begin());
            AddButton(temp, posX, posY, 150, 50, hwnd);
            int ligne = ((150 + 10 + separator) * 2) - (2 * separator);
            if (posX > ligne) {
                posY += 50 + 10;
                posX = 10;
            }
            else
                posX = 150 + posX + separator;
        }

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

    /// <summary>
    /// Add Button in window
    /// </summary>
    /// <param name="_title">Message in button</param>
    /// <param name="posX">Position X</param>
    /// <param name="posY">Position Y</param>
    /// <param name="_width">width of button</param>
    /// <param name="_heigth">heigth of button</param>
    /// <param name="_window">Window where button is created</param>
    void AddButton(const std::wstring& _title, const int& posX, const int& posY, const int& _width, const int& _heigth, HWND _window)
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
            NULL,       // No menu.
            (HINSTANCE)GetWindowLongPtr(_window, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.

    }
};


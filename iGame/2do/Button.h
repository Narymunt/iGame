
class __declspec(dllexport) CButton  
{
public:
	
	// tworzy na podstawie systemu pliku
	
	CButton(char cFileSystem[], char clicked_name[], 
		char onbutton_name[], char pimage_name[],
		IDirect3DDevice8	*pDevice);
	
	virtual ~CButton();

	virtual int Draw(float mousex, float mousey, bool left, bool center, bool right); // rysuj przycisk

	virtual void SetPosition(long lX, long lY);

	// hot coords
	
	virtual void SetHotCoords(long lXStart, long lYStart, long lXEnd, long lYEnd);

private:

	// gor�ce wsp�rz�dne ;) 

	long		m_lXStart;
	long		m_lYStart;
	long		m_lXEnd;
	long		m_lYEnd;

	CSprite		*m_pClicked;		// nacisniety
	CSprite		*m_pOnButton;		// mysz nad nim
	CSprite		*m_pImage;		// zwyczajny

	bool		m_bFE;			// first enter
	bool		m_bPressed;		// czy nacisniety ?

};

#endif // !defined(AFX_BUTTON_H__5E00FEAF_DE67_4436_9881_6636BBF0EC75__INCLUDED_)

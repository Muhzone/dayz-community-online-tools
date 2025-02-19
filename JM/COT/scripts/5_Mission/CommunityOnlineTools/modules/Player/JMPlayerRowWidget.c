class JMPlayerRowWidget extends ScriptedWidgetEventHandler 
{
	private Widget layoutRoot;

	private string m_GUID;

	TextWidget Name;
	ButtonWidget Button;
	CheckBoxWidget Checkbox;

	JMPlayerForm Menu;

	void OnWidgetScriptInit( Widget w )
	{
		layoutRoot = w;
		layoutRoot.SetHandler( this );
		Init();
	}

	void Init() 
	{
		Name = TextWidget.Cast(layoutRoot.FindAnyWidget("text_name"));
		Button = ButtonWidget.Cast(layoutRoot.FindAnyWidget("button"));
		Checkbox = CheckBoxWidget.Cast(layoutRoot.FindAnyWidget("checkbox"));
	}

	void Show()
	{
		layoutRoot.Show( true );
		Button.Show( true );
		Checkbox.Show( true );
		Name.Show( true );
		OnShow();
	}

	void Hide()
	{
		OnHide();
		Name.Show( false );
		Button.Show( false );
		Checkbox.Show( false );
		layoutRoot.Show( false );
	}

	void OnShow()
	{
	}

	void OnHide() 
	{
	}

	void Update() 
	{
		
	}

	ref Widget GetLayoutRoot() 
	{
		return layoutRoot;
	}

	void SetPlayer( string guid )
	{
		m_GUID = guid;
		
		if ( m_GUID == "" ) 
		{
			Hide();
		} else 
		{
			JMPlayerInstance player = GetPermissionsManager().GetPlayer( m_GUID );
			if ( player )
			{
				Show();

				Name.SetText( player.GetName() );

				if ( GetPermissionsManager().GetClientGUID() == m_GUID )
				{
					Name.SetColor( 0xFF2ECC71 );
				} else if ( player.HasPermission( "COT" ) )
				{
					Name.SetColor( 0xFFA85A32 );
				} else 
				{
					Name.SetColor( 0xFFFFFFFF );
				}

				if ( JM_GetSelected().IsSelected( m_GUID ) )
				{
					Checkbox.SetChecked( true );
				} else
				{
					Checkbox.SetChecked( false );
				}
			} else
			{
				Hide();
			}
		}
	}

	string GetGUID()
	{
		return m_GUID;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		if ( w == NULL )
		{
			return false;
		}

		if ( w == Checkbox )
		{
			JMScriptInvokers.MENU_PLAYER_CHECKBOX.Invoke( m_GUID, Checkbox.IsChecked() );

			return true;
		}

		if ( w == Button )
		{
			JMScriptInvokers.MENU_PLAYER_BUTTON.Invoke( m_GUID, !Checkbox.IsChecked() );

			return true;
		}

		return false;
	}
}
#pragma once

#include <string>

namespace FactoryMethod
{
	class CButton
	{
	public:
		CButton();
		virtual ~CButton();

		virtual void Render() = 0;
	};

	class C2DButton : public CButton
	{
	public:
		C2DButton();
		virtual ~C2DButton();

		virtual void Render();
	};

	class C3DButton : public CButton
	{
	public:
		C3DButton();
		virtual ~C3DButton();

		virtual void Render();
	};
}
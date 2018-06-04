#ifndef COMPONENT
#define COMPONENT

namespace FalconeEngine
{
	class Object;

	class Component
	{
	protected:
		FalconeEngine::Object * parent;
	public:
		Component();
		~Component();

		virtual void Start() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		void SetParent(FalconeEngine::Object * _parent)
		{
			this->parent = _parent;
		}

		FalconeEngine::Object * GetParent()
		{
			return this->parent;
		}
	};
}

#endif
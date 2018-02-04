#ifndef GUARD_PTY_DETAILS_DEFINE_PROPERTY_HPP__
#define GUARD_PTY_DETAILS_DEFINE_PROPERTY_HPP__

#define PTY_DETAILS_DEFINE_PROPERTY(name, in_processing) \
	template<class Base> struct name : Base { \
		protected: \
			using Base::self; \
			inline ~name() = default; \
		public: \
			in_processing\
	};

#endif

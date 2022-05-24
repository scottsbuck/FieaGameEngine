#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "json/json.h"

namespace FieaGameEngine
{
	class IJsonParseHelper;

	class JsonParseCoordinator
	{
		
	public:
		class SharedData : public RTTI
		{
			friend JsonParseCoordinator;

			RTTI_DECLARATIONS(SharedData, RTTI)
				
		public:
			/// <summary>
			/// virtual destructor
			/// </summary>
			virtual ~SharedData() = default;
			/// <summary>
			/// Initializes the shared data, setting depth to 0
			/// </summary>
			virtual void Initialize();
			/// <summary>
			/// CleanUp method (does nothing in the base class)
			/// </summary>
			virtual void CleanUp();
			/// <summary>
			/// Virtual constructor, constructs a new Shared Data
			/// </summary>
			/// <returns>returns a new shared data that you are responsible for deleting</returns>
			virtual SharedData* Create() const = 0;
			/// <summary>
			/// returns the json parse coordinator
			/// </summary>
			/// <returns>returns the json parse coordinator</returns>
			JsonParseCoordinator* GetJsonParseCoordinator();

			/// <summary>
			/// increases depth by 1
			/// </summary>
			void IncrementDepth();
			/// <summary>
			/// decrements depth by 1
			/// </summary>
			void DecrementDepth();
			/// <summary>
			/// returns the depth
			/// </summary>
			/// <returns>returns the depth</returns>
			size_t Depth();

		private:
			void SetJsonParseCoordinator(JsonParseCoordinator* parseCoordinator);

			size_t mDepth{ 0 };
			JsonParseCoordinator* mParseCoordinator{ nullptr };
		};

		/// <summary>
		/// Primary constructor for the coordinator
		/// </summary>
		/// <param name="data">the shared data created to pass in to associate with the parse coordinator</param>
		JsonParseCoordinator(SharedData& data);
		~JsonParseCoordinator();

		JsonParseCoordinator(JsonParseCoordinator& other) = delete;
		JsonParseCoordinator* operator=(JsonParseCoordinator& other) = delete;
		JsonParseCoordinator() = delete;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other">object to be moved</param>
		/// <returns>the move constructed object</returns>
		JsonParseCoordinator(JsonParseCoordinator&& other) noexcept;
		/// <summary>
		/// Move assignmnet operator
		/// </summary>
		/// <param name="other">object to be moved</param>
		/// <returns>move assigned object</returns>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& other) noexcept;
		/// <summary>
		/// Essentially a copy constructor but deals with memory better
		/// </summary>
		/// <returns>a pointer to a new parse coordinator that is the same as this</returns>
		JsonParseCoordinator* Clone();
		/// <summary>
		/// Adds a helper to the helper list
		/// </summary>
		/// <param name="parseHelper">parsehelper to add to the list</param>
		void AddHelper(IJsonParseHelper& parseHelper);
		/// <summary>
		/// Removes a helper from the helper list
		/// </summary>
		/// <param name="parseHelper">parsehelper to be removed</param>
		void RemoveHelper(IJsonParseHelper& parseHelper);
		/// <summary>
		/// returns bool checking if clone
		/// </summary>
		/// <returns>returns bool checking if clone</returns>
		bool IsClone();
		/// <summary>
		/// returns a const reference to a list of the helpers
		/// </summary>
		/// <returns>returns a const reference to a list of the helpers</returns>
		const Vector<IJsonParseHelper*>& Helpers();
		/// <summary>
		/// Initialize the parser, initializes all helpers
		/// </summary>
		void Initialize();
		/// <summary>
		/// Starts parse with a string
		/// </summary>
		/// <param name="string">json formatted string</param>
		void ParseObject(const std::string& string);
		/// <summary>
		/// Starts parse using a file name
		/// </summary>
		/// <param name="string">converts filestream to inputstream. File must be json formatted</param>
		void ParseObjectFromFile(const std::string& string);
		/// <summary>
		/// starts parse using inputstream
		/// </summary>
		/// <param name="inputStream">inputstream to convert to json object</param>
		void ParseObject(std::istream& inputStream);
		/// <summary>
		/// returns shared data
		/// </summary>
		/// <returns>returns shared data</returns>
		SharedData* GetSharedData();
		/// <summary>
		/// Sets shared data to data and sets datas parse associater to this
		/// </summary>
		/// <param name="data">new shared data to use</param>
		void SetSharedData(SharedData* data);

	private:
		void ParseMembers(const Json::Value& object, size_t index = 0);
		void Parse(const std::string& string, const Json::Value& object, size_t index = 0);

		bool mIsClone{ false };
		SharedData* mData{ nullptr };
		Vector<IJsonParseHelper*> mHelperList;
		std::string mFileName;
	};
}



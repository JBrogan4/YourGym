#include <iostream> // Used for std::cout
#include <vector> // Used for std::vector
#include <ctime> // Used for std::time and t_time
#include <algorithm> // Used for std::remove_if
#include <string> // Used for std::string

class Event { // Event class, containing event metadata, can return event data for comparisons
  private:
    int EventId; // Identifier, unique
    std::time_t EventTimestamp;  // Unix time
    std::string EventType; // Metadata - type
  
  public:
    // Constructor, initialise variables
    Event(int EventIdentifier, std::time_t EventTime, const std::string& EventCategory):
      EventId(EventIdentifier), 
      EventTimestamp(EventTime), 
      EventType(EventCategory) 
      {}
  
    // Getter functions
    int GetEventId() const { return EventId; }
    std::time_t GetEventTimestamp() const { return EventTimestamp; }
    std::string GetEventType() const { return EventType; }
  
    // Display function
    void DisplayEvent() const {
      char TimeBuffer[26]; // ctime returns a 26-char string
      std::strftime(TimeBuffer, sizeof(TimeBuffer), "%c", std::localtime(&EventTimestamp)); // Convert time to string without newline
      
      std::cout << "Event ID: " << EventId
                << ", Time: " << TimeBuffer
                << ", Type: " << EventType << std::endl;
    }
};

class Events { // Class of events, stores all event classes, can add / remove
  private:
      std::vector<Event> EventList;
  
  public:
    void AddEvent(int EventIdentifier, std::time_t EventTime, const std::string& EventCategory) { // Add a new event AddEvent(ID, Time, Type)
      EventList.emplace_back(EventIdentifier, EventTime, EventCategory);
      std::cout << "Event added successfully.\n";
    }
  
    void RemoveEvent(int EventIdentifier) { // Remove event from events list by event id RemoveEvent(Id)
      auto Iterator = std::remove_if( // Iterate through events
        EventList.begin(),
        EventList.end(),
        
        [EventIdentifier](const Event& CurrentEvent) {
          return CurrentEvent.GetEventId() == EventIdentifier;
        }
        
      );
  
      if (Iterator != EventList.end()) {
        EventList.erase(Iterator, EventList.end());
        std::cout << "Event removed successfully.\n";
      } else {
        std::cout << "Event not found.\n";
      }
    }
  
    // Display all events
    void DisplayAllEvents() const {
      for (const auto& CurrentEvent : EventList) {
        CurrentEvent.DisplayEvent();
      }
    }
};

int main() { // Test script
  Events EventManager;

  std::time_t CurrentTime = std::time(nullptr); // Get current time in unix
  EventManager.AddEvent(1, CurrentTime, "Spin");

  std::tm TimeStructure = {};
  TimeStructure.tm_year = 2026 - 1900; // Year of event - 1900
  TimeStructure.tm_mon  = 3 - 1; // Month of event - 1
  TimeStructure.tm_mday = 20; // Day of month of event
  TimeStructure.tm_hour = 14; // Hour of event
  TimeStructure.tm_min  = 0; // Minute of event
  TimeStructure.tm_sec  = 0; // Seconds of event

  std::time_t SpecificEventTime = std::mktime(&TimeStructure);
  EventManager.AddEvent(2, SpecificEventTime, "Circuit");

  EventManager.DisplayAllEvents(); // Check events are added

  EventManager.RemoveEvent(1);

  EventManager.DisplayAllEvents(); // Check event 1 is removed

  return 0;
}
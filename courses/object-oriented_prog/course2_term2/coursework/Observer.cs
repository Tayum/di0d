using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    // PATTERN: Observer
    public enum EVENT_TYPE
    {
        ADDTOCART,
        REMOVEFROMCART,
        BUYITEMS
    }


    public interface IEventListener
    {
        void update(EVENT_TYPE eventType, string info);
    }


    public class EventManager
    {
        // There can be only one listener at the same time for each event:
        // only Current Menu is the listener. 
        Dictionary<EVENT_TYPE, IEventListener> listeners = new Dictionary<EVENT_TYPE, IEventListener>();


        public EventManager(params EVENT_TYPE[] events)
        {
            foreach(EVENT_TYPE ev in events)
            {
                listeners.Add(ev, null);
            }
        }


        public void subscribe(EVENT_TYPE ev, IEventListener listener)
        {
            if (listeners.ContainsKey(ev))
            {
                listeners[ev] = listener;
            }
        }

        public void unsubscribe(EVENT_TYPE ev, IEventListener listener)
        {
            if (listeners.ContainsKey(ev))
            {
                listeners[ev] = null;
            }
        }

        public void notify(EVENT_TYPE ev, string info)
        {
            if(listeners.ContainsKey(ev))
            {
                listeners[ev].update(ev, info);
            }
        }
    }
}

#include "IEconItemsParser.hpp"
#include <memory>

using namespace Util::String;

#define ATTR_INDEX_EFFECT       134
#define ATTR_INDEX_CRAFT_NUMBER 229

/**
 * Get Player Items URL.
 */
static const char * URL_ITEMS =
	"http://api.steampowered.com/IEconItems_%d/GetPlayerItems/v0001?SteamId=%s"
;

/**
 * IEconItems_<ID> IDs:
 * https://wiki.teamfortress.com/wiki/WebAPI#appids
 *  - TF 2 : 440
 *  - Dota 2 : 570
 *  - Portal 2: 620
 *  - CSGO: ?
 */

string IEconItemsParser::itemsUrl(User::Ptr user)
{
	return format(URL_ITEMS, econId(), "76561198012196517");//user->getId64());
}

void parseItem(Response::JsonValue& invItem, Item::Ptr item)
{
	Response::JsonValue emptyValue;

	item->id(invItem.get("id", emptyValue).asUInt64());
	item->tradable(!invItem.get("flag_cannot_trade", emptyValue).asBool());
	item->craftable(!invItem.get("flag_cannot_craft", emptyValue).asBool());
	item->defindex(invItem.get("defindex", emptyValue).asInt());
	item->quality(invItem.get("quality", emptyValue).asInt());
	item->level(invItem.get("level", emptyValue).asInt());
	item->origin(invItem.get("origin", emptyValue).asInt());
	for (auto attr : invItem.get("attributes", emptyValue)) {
		switch (attr.get("defindex", emptyValue).asInt()) {
		case ATTR_INDEX_CRAFT_NUMBER :
			item->craftNumber(attr.get("value", emptyValue).asInt());
			break;
		case ATTR_INDEX_EFFECT:
			item->effect(attr.get("float_value", emptyValue).asFloat());
			break;
		}
	}
}

int parseItems(Response::JsonValue& items, User::Ptr user, PushQueue<Item::Ptr>::Ptr queue)
{
	Item::Ptr item = std::make_shared<Item>(user);
	int count = 0;

	if (!items)
		return count;

	for (auto invItem : items) {
		item->reset();

		parseItem(invItem, item);

		queue->push(item);
		count++;
	}

	return count;
}

int IEconItemsParser::items(Response& resp, User::Ptr user)
{
	Response::JsonValue emptyValue, items;

	// Prepare the tree
	items = (*resp.json())
			.get("result", emptyValue)
			.get("items", emptyValue)
	;

	// Process the tree
	return parseItems(items, user, queue());
}

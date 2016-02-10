#include "ItemQueue.hpp"

typedef ItemQueue::Column Column;

/**
 * The Table the items are stored in.
 */
static const char * QUEUE_TABLE =
    "tf2_user_item"
;

/**
 * The formatting string for inserting items into the database.
 */
static const char * QUERY_INSERT =
    "%lld,%s,%d,%d,%d,%d,%d,%d,%d"
;

/**
 * The columns that need values when inserting.
 */
static Column::Name QUEUE_COLUMNS[9] = {
    "id",
    "steamid",
    "defindex",
    "effect",
    "level",
    "quality",
    "craftable",
    "tradable",
    "craft_number"
};

Column::Array ItemQueue::columns() const
{
	return Column::Array(
        QUEUE_COLUMNS,
        QUEUE_COLUMNS + sizeof(QUEUE_COLUMNS) / sizeof(Column::Name)
    );
}

std::string ItemQueue::table()
{
	return db->prefixed(QUEUE_TABLE);
}

void ItemQueue::push(Item::Ptr item)
{
    string query = Util::String::format(
        QUERY_INSERT,
        item->id(),
        item->user()->getId32(),
        item->defindex(),
        item->effect(),
        item->level(),
        item->quality(),
        item->craftable(),
        item->tradable(),
        item->craftNumber()
    );

	queueInsert(query);
}


#include "../../include/dbcppp/CApi.h"
#include "NetworkImpl.h"

using namespace dbcppp;

extern "C"
{
	const char* dbcppp_NetworkGetVersion(struct dbcppp_Network* net)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		return neti->getComment().c_str();
	}
	bool dbcppp_NetworkHasNewSymbol(struct dbcppp_Network* net, const char* new_symbol)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		return neti->hasNewSymbol(new_symbol);
	}
	void dbcppp_NetworkForEachNewSymbol(struct dbcppp_Network* net, void(*cb)(const char*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachNewSymbol(
			[&](const std::string& n)
			{
				cb(n.c_str());
			});
	}
	struct dbcppp_BitTiming* dbcppp_NetworkGetBitTiming(struct dbcppp_Network* net)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const BitTiming& bt = neti->getBitTiming();
		return reinterpret_cast<dbcppp_BitTiming*>(&const_cast<BitTiming&>(bt));
	}
	struct dbcppp_Node* dbcppp_NetworkGetNodeByName(struct dbcppp_Network* net, const char* name)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Node* node = neti->getNodeByName(name);
		return reinterpret_cast<dbcppp_Node*>(const_cast<Node*>(node));
	}
	void dbcppp_network_for_each_node(struct dbcppp_Network* net, void(*cb)(dbcppp_Node*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachNode(
			[&](const Node& node)
			{
				cb(reinterpret_cast<dbcppp_Node*>(&const_cast<Node&>(node)));
			});
	}
	struct dbcppp_ValueTable* dbcppp_NetworkGetValueTableByName(struct dbcppp_Network* net, const char* name)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const ValueTable* vt = neti->getValueTableByName(name);
		return reinterpret_cast<dbcppp_ValueTable*>(const_cast<ValueTable*>(vt));
	}
	struct dbcppp_ValueTable* dbcppp_NetworkFindValueTable(struct dbcppp_Network* net, bool(*pred)(struct dbcppp_ValueTable*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const ValueTable* vt = neti->findValueTable(
			[&](const ValueTable& vt)
			{
				return pred(reinterpret_cast<dbcppp_ValueTable*>(&const_cast<ValueTable&>(vt)));
			});
		return reinterpret_cast<dbcppp_ValueTable*>(const_cast<ValueTable*>(vt));
	}
	void dbcppp_NetworkForEachValueTale(struct dbcppp_Network* net, void(*cb)(struct dbcppp_ValueTable*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachValueTable(
			[&](const ValueTable& vt)
			{
				cb(reinterpret_cast<dbcppp_ValueTable*>(&const_cast<ValueTable&>(vt)));
			});
	}
	struct dbcppp_Message* dbcppp_NetworkGetMessageById(struct dbcppp_Network* net, uint64_t id)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Message* m = neti->getMessageById(id);
		return reinterpret_cast<dbcppp_Message*>(const_cast<Message*>(m));
	}
	struct dbcppp_Message* dbcppp_NetworkFindMessage(struct dbcppp_Network* net, bool(*pred)(struct dbcppp_Message*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Message* m = neti->findMessage(
			[&](const Message& m)
			{
				return pred(reinterpret_cast<dbcppp_Message*>(&const_cast<Message&>(m)));
			});
		return reinterpret_cast<dbcppp_Message*>(const_cast<Message*>(m));
	}
	void dbcppp_NetworkForEachMessage(struct dbcppp_Network* net, void(*cb)(struct dbcppp_Message*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachMessage(
			[&](const Message& m)
			{
				cb(reinterpret_cast<dbcppp_Message*>(&const_cast<Message&>(m)));
			});
	}
	struct dbcppp_EnvironmentVariable* dbcppp_NetworkGetEnvironmentVariableByName(struct dbcppp_Network* net, const char* name)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const EnvironmentVariable* ev = neti->getEnvironmentVariableByName(name);
		return reinterpret_cast<dbcppp_EnvironmentVariable*>(const_cast<EnvironmentVariable*>(ev));
	}
	struct dbcppp_EnvironmentVariable* dbcppp_NetworkFindEnvironmentVariable(struct dbcppp_Network* net, bool(*pred)(struct dbcppp_EnvironmentVariable*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const EnvironmentVariable* ev = neti->findEnvironmentVariable(
			[&](const EnvironmentVariable& ev)
			{
				return pred(reinterpret_cast<dbcppp_EnvironmentVariable*>(&const_cast<EnvironmentVariable&>(ev)));
			});
		return reinterpret_cast<dbcppp_EnvironmentVariable*>(const_cast<EnvironmentVariable*>(ev));
	}
	void dbcppp_NetworkForEachEnvironmentVariable(struct dbcppp_Network* net, void(*cb)(struct dbcppp_EnvironmentVariable*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachEnvironmentVariable(
			[&](const EnvironmentVariable& ev)
			{
				cb(reinterpret_cast<dbcppp_EnvironmentVariable*>(&const_cast<EnvironmentVariable&>(ev)));
			});
	}
	struct dbcppp_AttributeDefinition* dbcppp_NetworkGetAttributeDefinitionByName(struct dbcppp_Network* net, const char* name)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const AttributeDefinition* ad = neti->getAttributeDefinitionByName(name);
		return reinterpret_cast<dbcppp_AttributeDefinition*>(const_cast<AttributeDefinition*>(ad));
	}
	struct dbcppp_AttributeDefinition* dbcppp_NetworkFindAttributeDefinition(struct dbcppp_Network* net, bool(*pred)(struct dbcppp_AttributeDefinition*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const AttributeDefinition* ad = neti->findAttributeDefinition(
			[&](const AttributeDefinition& ad)
			{
				return pred(reinterpret_cast<dbcppp_AttributeDefinition*>(&const_cast<AttributeDefinition&>(ad)));
			});
		return reinterpret_cast<dbcppp_AttributeDefinition*>(const_cast<AttributeDefinition*>(ad));
	}
	void dbcppp_NetworkForEachAttributeDefinition(struct dbcppp_Network* net, void(*cb)(struct dbcppp_AttributeDefinition*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachAttributeDefinition(
			[&](const AttributeDefinition& ad)
			{
				cb(reinterpret_cast<dbcppp_AttributeDefinition*>(&const_cast<AttributeDefinition&>(ad)));
			});
	}
	struct dbcppp_Attribute* dbcppp_NetworkGetAttributeDefaultByName(struct dbcppp_Network* net, const char* name)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Attribute* ad = neti->getAttributeDefaultByName(name);
		return reinterpret_cast<dbcppp_Attribute*>(const_cast<Attribute*>(ad));
	}
	struct dbcppp_Attribute* dbcppp_NetworkFindAttributeDefault(struct dbcppp_Network* net, bool(*pred)(struct dbcppp_Attribute*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Attribute* ad = neti->findAttributeDefault(
			[&](const Attribute& ad)
			{
				return pred(reinterpret_cast<dbcppp_Attribute*>(&const_cast<Attribute&>(ad)));
			});
		return reinterpret_cast<dbcppp_Attribute*>(const_cast<Attribute*>(ad));
	}
	void dbcppp_NetworkForEachAttributeDefault(struct dbcppp_Network* net, void(*cb)(struct dbcppp_Attribute*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachAttributeDefault(
			[&](const Attribute& ad)
			{
				cb(reinterpret_cast<dbcppp_Attribute*>(&const_cast<Attribute&>(ad)));
			});
	}
	struct dbcppp_Attribute* dbcppp_NetworkGetAttributeValueByName(struct dbcppp_Network* net, const char* name)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Attribute* ad = neti->getAttributeValueByName(name);
		return reinterpret_cast<dbcppp_Attribute*>(const_cast<Attribute*>(ad));
	}
	struct dbcppp_Attribute* dbcppp_NetworkFindAttributeValue(struct dbcppp_Network* net, bool(*pred)(struct dbcppp_Attribute*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		const Attribute* ad = neti->findAttributeValue(
			[&](const Attribute& ad)
			{
				return pred(reinterpret_cast<dbcppp_Attribute*>(&const_cast<Attribute&>(ad)));
			});
		return reinterpret_cast<dbcppp_Attribute*>(const_cast<Attribute*>(ad));
	}
	void dbcppp_NetworkForEachAttributeValue(struct dbcppp_Network* net, void(*cb)(struct dbcppp_Attribute*))
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		neti->forEachAttributeValue(
			[&](const Attribute& ad)
			{
				cb(reinterpret_cast<dbcppp_Attribute*>(&const_cast<Attribute&>(ad)));
			});
	}
	const char* dbcppp_NetworkGetComment(struct dbcppp_Network* net)
	{
		const NetworkImpl* neti = reinterpret_cast<NetworkImpl*>(net);
		return neti->getComment().c_str();
	}
}
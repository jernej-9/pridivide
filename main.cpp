#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Transaction
{
public:
	Transaction(
		int payerID, int recipientID, double amount, std::string comment = ""
	)
		: m_payerID { payerID }, m_recipientID { recipientID },
		  m_amount { amount }, m_comment { comment }
	{
		if (m_payerID == m_recipientID)
		{
			std::cout <<
				"Invalid transaction: Payer and recipient should not be the "
				"same.\n";
		}
	}

	void print()
	{
		std::cout << "Payer: " << m_payerID << '\t'
			<< "Recipient: " << m_recipientID << '\t'
			<< "Amount: " << m_amount << '\n';

		if (m_comment != "")
			std::cout << "\tComment: " << m_comment << '\n';
	}

	const int m_payerID;
	const int m_recipientID;
	const double m_amount;

private:
	const std::string m_comment;
};

class Ledger
{
public:
	Ledger(): m_names {}, m_transactions {}
	{
	}

	void addTransaction(
		const std::string payerName, const std::string recipientName,
		const double amount, const std::string comment
	)
	{
		m_transactions.push_back(
			Transaction{
				getID(payerName), getID(recipientName), amount, comment
			}
		);
	}

	void printTransactions()
	{
		for (Transaction trans : m_transactions)
			trans.print();
	}

	// calculateBalances()
	// settle()

private:
	int getID(std::string name)
	{
		// Check if name is already in m_names
		auto found { std::find(m_names.begin(), m_names.end(), name) };

		// If it is, the person already has an ID
		if (found != m_names.end())
		{
			std::cout << "Name already exists\n";

			// Return index of the name in m_names
			return found - m_names.begin();
		}
		// If it is not, add the name to m_names and return new ID
		else
		{
			std::cout << "New name\n";

			m_names.push_back(name);
			// New ID is the index of last element
			return m_names.size() - 1;
		}
	}

	// Array of names of the people involved. ID = i corresponds to m_names[i]
	std::vector<std::string> m_names;

	std::vector<Transaction> m_transactions;
};

int main()
{
	Ledger ledger;
	ledger.addTransaction("Robert", "Mike", 33.28, "For pizza");
	ledger.printTransactions();

	return 0;
}

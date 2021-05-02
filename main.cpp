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

	void getTransactionFromUser()
	{
		std::cout << "Name of payer: ";
		std::string payerName { "" };
		std::cin >> payerName;

		std::cout << "Name of recipient: ";
		std::string recipientName { "" };
		std::cin >> recipientName;

		if (payerName == recipientName)
		{
			std::cout <<
				"Payer and recipient should not be the same. Try again.\n";
			return;
		}

		std::cout << "Amount: ";
		double amount { 0.0 };
		std::cin >> amount;

		if (amount <= 0.0)
		{
			std::cout << "Amount should be positive. Try again.\n";
			return;
		}

		std::cout << "Comment: ";
		std::string comment { "" };
		// Clear buffer up to and including a \n
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, comment);

		addTransaction(payerName, recipientName, amount, comment);
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

void printListOfCommands()
{
	std::cout <<
		"a\tAdd a transaction to the ledger\n"
		"c\tPrint a list of accepted commands\n"
		"p\tPrint all transactions in the ledger\n"
		"q\tQuit program\n";
}

int main()
{
	Ledger ledger;
	// ledger.addTransaction("Robert", "Diana", 33.28, "For pizza");
	// ledger.printTransactions();

	std::cout <<
		"pridivide version 0.0\n"
		"Type 'c' for a list of commands\n";
	while (true)
	{
		// Print prompt
		std::cout << "(pridivide) ";
		char input { '\0' };
		std::cin >> input;

		switch (input)
		{
			case 'a':
				ledger.getTransactionFromUser();
				break;
			case 'c':
				printListOfCommands();
				break;
			case 'p':
				ledger.printTransactions();
				break;
			case 'q':
				return 0;
		}
	}

	return 0;
}

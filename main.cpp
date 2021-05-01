#include <iostream>
#include <string>

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

int main()
{
	Transaction tran { 0, 1, 14.5, "For pizza" };

	tran.print();

	return 0;
}

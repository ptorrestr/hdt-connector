from hdtconnector.libhdtconnector import HDTConnector

if __name__ == "__main__":
	m_file = "etc/test.hdt"
	m_map = HDTConnector(m_file, True)
	triple = next(m_map.search("", "", ""))

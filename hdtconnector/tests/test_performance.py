import numpy as np
from itertools import islice
from hdtconnector.libhdtconnector import HDTConnector
from hdtconnector.libhdtconnector import triple_role
import pytest

m_file = "etc/test.hdt"

def iterator_triple_id(m_map, type_):
    triples = np.array(
        [ subject
            for subject, _, _ in m_map.search_id(0, 0, 0)]
        , dtype = type_)
    return 1

@pytest.mark.parametrize("type_", ["u4","u8"])
def test_iterator_triple_id(benchmark, type_):
    m_map = HDTConnector(m_file)
    result = benchmark(iterator_triple_id, m_map, type_)

def iterator_triple_id_ext(m_map, type_):
    triples = np.array(
        [( object_, is_shared, is_literal)
            for _, _, object_, is_shared, _, is_literal in m_map.search_id(0, 0, 0, True)]
        , dtype = type_)
    return 1

@pytest.mark.parametrize("type_", ["u4,bool,bool","u8,bool,bool"])
@pytest.mark.parametrize("file_name", ["test.hdt", "test_literal.hdt"])
def test_iterator_triple_id_ext(benchmark, type_, file_name):
    m_map = HDTConnector( "etc/" + file_name)
    result = benchmark(iterator_triple_id_ext, m_map, type_)

def iterator_triple_id_is_literal(m_map, type_):
    is_literal = m_map.is_literal
    triples = np.array(
        [( subject, is_literal(subject))
            for subject, _, _ in m_map.search_id(0, 0, 0)]
        , dtype = type_ )
    return 1

@pytest.mark.parametrize("type_", ["u4,bool","u8,bool"])
@pytest.mark.parametrize("file_name", ["test.hdt", "test_literal.hdt"])
def test_iterator_triple_id_is_literal(benchmark, type_, file_name):
    m_map = HDTConnector("etc/" + file_name)
    result = benchmark(iterator_triple_id_is_literal, m_map, type_)

def iterator_triple_id_is_shared(m_map, type_):
    is_shared = m_map.is_shared
    triples = np.array(
        [( subject, is_shared(subject))
            for subject, _, _ in m_map.search_id(0, 0, 0)]
        , dtype = type_ )
    return 1

@pytest.mark.parametrize("type_", ["u4,bool","u8,bool"])
def test_iterator_triple_id_is_shared(benchmark, type_):
    m_map = HDTConnector(m_file)
    result = benchmark(iterator_triple_id_is_shared, m_map, type_)

def iterator_triple_id_is_shared_is_literal(m_map, type_):
    is_shared = m_map.is_shared
    is_literal = m_map.is_literal
    triples = np.array(
        [( object_ , is_shared(object_), is_literal(object_))
            for _,_,object_ in m_map.search_id(0, 0, 0)]
        , dtype = type_)
    return 1

@pytest.mark.parametrize("type_", ["u4,bool,bool","u8,bool,bool"])
@pytest.mark.parametrize("file_name", ["test.hdt", "test_literal.hdt"])
def test_iterator_triple_id_is_shared_is_literal(benchmark, type_, file_name):
    m_map = HDTConnector("etc/" + file_name)
    result = benchmark(iterator_triple_id_is_shared_is_literal, m_map, type_)

def iterator_triple_string(m_map):
    triples = np.array(
        [( subject, object_)
            for subject, _, object_ in m_map.search("", "", "")]
        )
    return 1

def test_iterator_triple_string(benchmark):
    m_map = HDTConnector(m_file)
    result = benchmark(iterator_triple_string, m_map)

def iterator_triple_indexed(m_map, type_,num_shared):
    subject = np.array (
            [ (subject, False)
                for subject, _, object_ in m_map.search_id(0, 0, 0)]
            , dtype = type_)
    subject['f1'][ subject['f0'] < num_shared ] = True
    return 1

@pytest.mark.parametrize("type_", ["u4,bool","u8,bool"])
def test_iterator_triple_indexed(benchmark, type_):
    m_map = HDTConnector("etc/test_literal.hdt")
    result = benchmark(iterator_triple_indexed, m_map, type_, 0)
